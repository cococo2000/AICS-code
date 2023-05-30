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

#include "cnplugin.h"
#include "plugin_batch_matmul_v2_kernel.h"

cnmlStatus_t cnmlCreatePluginBatchMatMulV2OpParam(
  cnmlPluginBatchMatMulV2OpParam_t *param,
  float scale_0,
  int pos_0,
  float scale_1,
  int pos_1,
  int dim_0,
  int dim_1,
  int m,
  int n,
  int k,
  cnmlCoreVersion_t core_version
) {
  // CHECK_ENFORCE(param, "param shouldn't be nullptr");
  *param = new cnmlPluginBatchMatMulV2OpParam();

  // scalar params
  (*param)->scale_0 = scale_0;
  (*param)->pos_0 = pos_0;
  (*param)->scale_1 = scale_1;
  (*param)->pos_1 = pos_1;
  (*param)->dim_0 = dim_0;
  (*param)->dim_1 = dim_1;
  (*param)->m = m;
  (*param)->n = n;
  (*param)->k = k;
  (*param)->core_version = core_version;

  return CNML_STATUS_SUCCESS;
}

cnmlStatus_t cnmlDestroyPluginBatchMatMulV2OpParam(
  cnmlPluginBatchMatMulV2OpParam_t *param
) {
  delete (*param);
  *param = nullptr;

  return CNML_STATUS_SUCCESS;
}

cnmlStatus_t cnmlCreatePluginBatchMatMulV2Op(
  cnmlBaseOp_t *op,
  cnmlPluginBatchMatMulV2OpParam_t param,
  cnmlTensor_t *input_tensors,
  cnmlTensor_t *output_tensors
) {
  // TODO 补全cnmlCreatePluginBatchMatMulV2Op函数
  float scale_0 = param->scale_0;
  int pos_0     = param->pos_0  ;
  float scale_1 = param->scale_1;
  int pos_1     = param->pos_1  ;
  int dim_0     = param->dim_0  ;
  int dim_1     = param->dim_1  ;
  int m         = param->m      ;
  int n         = param->n      ;
  int k         = param->k      ;

  const int input_num = 2;
  const int output_num = 1;

  cnrtKernelParamsBuffer_t params;
  cnrtGetKernelParamsBuffer(&params);
  cnrtKernelParamsBufferMarkInput(params);
  cnrtKernelParamsBufferMarkInput(params);
  cnrtKernelParamsBufferMarkOutput(params);
  cnrtKernelParamsBufferAddParam(params, &dim_0, sizeof(int));
  cnrtKernelParamsBufferAddParam(params, &dim_1, sizeof(int));
  cnrtKernelParamsBufferAddParam(params, &m, sizeof(int));
  cnrtKernelParamsBufferAddParam(params, &n, sizeof(int));
  cnrtKernelParamsBufferAddParam(params, &k, sizeof(int));
  cnrtKernelParamsBufferAddParam(params, &scale_0, sizeof(float));
  cnrtKernelParamsBufferAddParam(params, &pos_0, sizeof(int));
  cnrtKernelParamsBufferAddParam(params, &scale_1, sizeof(float));
  cnrtKernelParamsBufferAddParam(params, &pos_1, sizeof(int));

  void** InterfacePtr;
  InterfacePtr = reinterpret_cast<void **>(&BatchMatMulV2Kernel_MLU270_half);

  cnmlCreatePluginOp(op,
                     "MLUBatchMatMulV2",
                     InterfacePtr,
                     params,
                     input_tensors,
                     input_num,
                     output_tensors,
                     output_num,
                     nullptr,
                     0);

  cnrtDestroyKernelParamsBuffer(params);

  return CNML_STATUS_SUCCESS;
}

cnmlStatus_t cnmlComputePluginBatchMatMulV2OpForward(
  cnmlBaseOp_t op,
  void **inputs,
  int input_num,
  void **outputs,
  int output_num,
  cnrtQueue_t queue
) {
  // TODO 补全cnmlComputePluginBatchMatMulV2OpForward
  cnmlComputePluginOpForward_V4(op,
                                nullptr,
                                inputs,
                                input_num,
                                nullptr,
                                outputs,
                                output_num,
                                queue,
                                nullptr);

  return CNML_STATUS_SUCCESS;
}


