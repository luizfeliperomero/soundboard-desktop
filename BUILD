cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = ["//src/player:player", "//src/textbox:textbox"],
     linkopts = [
        "-lsfml-graphics",
        "-lsfml-window",
        "-lsfml-system",
        "-lsfml-audio",
    ]
)
