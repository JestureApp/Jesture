load("//qt:qt.bzl", "qt_qrc")
load("//jesture/tool:app.bzl", "app")

package(default_visibility = ["//visibility:public"])

# cc_binary(
#     name = "jesture",
#     srcs = [
#         "jesture.cc",
#     ],
#     data = [
#         "@mediapipe//mediapipe/modules/hand_landmark:com_google_mediapipe_hand_landmark_full_tflite_ln",
#     ],
# )

qt_qrc(
    name = "jesture_qrc",
    out = "jesture.qrc",
    data = [
        "@mediapipe//mediapipe/modules/palm_detection:palm_detection_full.tflite",
        "@mediapipe//mediapipe/modules/palm_detection:palm_detection_lite.tflite",
    ],
    files = [
        "mediapipe/modules/palm_detection:palm_detection_full.tflite",
    ],
)

app(
    name = "jesture",
    bin_srcs = [
        "jesture.cc",
    ],
)
