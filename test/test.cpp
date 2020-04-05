/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "dash_parser.h"
#include "mpd.h"

#include <chrono>
#include <iostream>

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *fp;
  dash::mpd::DASHParser dash_parser;
  std::unique_ptr<dash::mpd::MPD> mpdTree;

  for (int arg_ctr = 2; arg_ctr <= argc; arg_ctr++) {
    if (argc < arg_ctr || NULL == (fp = fopen(argv[arg_ctr - 1], "r"))) {
      printf("Failed to open file\n");
      return 1;
    }
    printf("#######Parsing %s\n", argv[arg_ctr - 1]);
    fseek(fp, 0L, SEEK_END);
    size_t buffer_sz = ftell(fp);
    auto buffer = std::make_unique<char[]>(buffer_sz);
    memset(buffer.get(), 0, buffer_sz);
    fseek(fp, 0L, SEEK_SET);
    size_t file_size = fread(buffer.get(), sizeof(char), buffer_sz, fp);
    if (file_size) {
      std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
      mpdTree = dash_parser.Parse(buffer.get(), buffer_sz);
      std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
      std::cout << "Parsing Took " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    }
    fclose(fp);
    printf("##Parsing %s\n\n", mpdTree ? "Successful" : "Failed");
  }
  return 0;
}
