// MIT License
// Copyright (c) 2024-2025 Tomáš Mark

#include "../src/AppCore.hpp"
#include <gtest/gtest.h>

#if defined(PLATFORM_WEB)
  #include <emscripten/emscripten.h>
#endif

TEST (WebAppCppSdl2Logic, HandlesArguments) {
  const char* argv[] = { "WebAppCppSdl2", "--help" };
  EXPECT_EQ (runWebAppCppSdl2 (2, argv), 0);
}

TEST (WebAppCppSdl2Logic, HandlesArgumentsNoLibrary) {
  const char* argv[] = { "WebAppCppSdl2", "--omit" };
  EXPECT_EQ (runWebAppCppSdl2 (2, argv), 0);
}

TEST (WebAppCppSdl2Logic, HandlesArgumentsLog2File) {
  const char* argv[] = { "WebAppCppSdl2", "--log2file" };
  EXPECT_EQ (runWebAppCppSdl2 (2, argv), 0);
}
