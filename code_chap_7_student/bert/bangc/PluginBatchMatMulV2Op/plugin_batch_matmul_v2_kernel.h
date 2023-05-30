/*************************************************************************
 * Copyright (C) [2020] by Cambricon, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *************************************************************************/

#ifndef _PLUGIN_BATCH_MATMUL_V2_KERNEL_H
#define _PLUGIN_BATCH_MATMUL_V2_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif
// TODO：完成接口定义
void BatchMatMulV2Kernel_MLU270_half(
    void* left_ddr,         // GDRAM上的左矩阵
    void* right_ddr,        // GDRAM上的右矩阵
    void* dst_ddr,          // GDRAM上的输出矩阵
    int dim_0,              // 输入维度，左右矩阵的第一维
    int dim_1,              // 输入维度，左右矩阵的第二维
    int m,                  // 输入维度，左矩阵的第三维
    int n,                  // 输入维度，右矩阵的第四维
    int k,                  // 输入维度，左矩阵的第四维，右矩阵的第三维
    float scale_0,          // 左矩阵的量化scale参数
    int pos_0,              // 左矩阵的量化pos参数
    int scale_1,            // 右矩阵的量化scale参数
    int pos_1               // 右矩阵的量化pos参数
);

#ifdef __cplusplus
}
#endif
#endif

