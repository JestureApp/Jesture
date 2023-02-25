#include "jesture/jesturepipe/worker.h"

#include <map>

#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace jesture {
namespace {
constexpr char kOutputStream[] = "annotated_frame";
}

absl::StatusOr<JesturePipeWorker> JesturePipeWorker::Create(
    JesturePipeInit init) noexcept {
    JesturePipeWorker worker;

    MP_RETURN_IF_ERROR(jesturepipe::jesturepipe_graph(
        worker.graph.get(), init.palm_model_full_path,
        init.palm_model_lite_path, init.landmark_model_full_path,
        init.landmark_model_lite_path));

    return worker;
}

JesturePipeWorker::JesturePipeWorker() noexcept : abort_requested(false) {
    graph = std::make_unique<mediapipe::CalculatorGraph>();
}

JesturePipeWorker::JesturePipeWorker(JesturePipeWorker &&other) noexcept
    : graph(std::move(other.graph)) {}

JesturePipeWorker &JesturePipeWorker::operator=(
    JesturePipeWorker &&other) noexcept {
    if (this != &other) {
        graph = std::move(other.graph);
    }

    return *this;
}

absl::Status JesturePipeWorker::Start(JesturePipeSettings settings) noexcept {
    abort_requested.store(false);

    ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller poller,
                     graph->AddOutputStreamPoller(kOutputStream));

    const std::map<std::string, mediapipe::Packet> side_packets = {
        {"camera_index", mediapipe::MakePacket<int>(settings.camera_index)
                             .At(mediapipe::Timestamp(0))},
        {"mode",
         mediapipe::MakePacket<int>(settings.mode).At(mediapipe::Timestamp(0))},
        {"num_hands", mediapipe::MakePacket<int>(settings.num_hands)
                          .At(mediapipe::Timestamp(0))}};

    MP_RETURN_IF_ERROR(graph->StartRun(side_packets));

    while (!abort_requested.load()) {
        mediapipe::Packet packet;

        if (!poller.Next(&packet)) break;

        auto &output_frame = packet.Get<mediapipe::ImageFrame>();

        cv::Mat output_frame_mat = mediapipe::formats::MatView(&output_frame);
        cv::cvtColor(output_frame_mat, output_frame_mat, cv::COLOR_RGB2BGR);

        frameReady(output_frame_mat);
    }

    MP_RETURN_IF_ERROR(graph->CloseAllPacketSources());

    return graph->WaitUntilDone();
}

void JesturePipeWorker::Stop() noexcept { abort_requested.store(true); }
}  // namespace jesture