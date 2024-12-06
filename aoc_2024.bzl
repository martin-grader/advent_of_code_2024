load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_cc//cc:defs.bzl", "cc_library")
load("@rules_cc//cc:defs.bzl", "cc_test")

def aoc_2024_cc_binary(number):
    cc_binary(
        name = 'puzzle_'+number,
        deps = ['puzzle_'+number+'_input'],
        srcs = ['main.cpp'],
        copts = [
            "-Wall",
            "-std=c++17",
            ],
    )
def aoc_2024_cc_library(number):
    cc_library(
        name = 'puzzle_'+number+'_input',
        hdrs = native.glob(["*.hpp"]),
        visibility = ['//visibility:public']
    )
def aoc_2024_cc_test(number):
    cc_test(
        name = "puzzle_"+number+"_test",
        size = "small",
        srcs = ["puzzle_"+number+".cpp"],
        deps = [
            "//puzzle_"+number+":puzzle_"+number+"_input",
            "@googletest//:gtest",
            "@googletest//:gtest_main",
        ],
        copts = [
            "-Wall",
            "-std=c++17",
            ],
    )
