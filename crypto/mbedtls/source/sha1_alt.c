/****************************************************************************
 * apps/crypto/mbedtls/source/sha1_alt.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include "mbedtls/sha1.h"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

void mbedtls_sha1_clone(FAR mbedtls_sha1_context *dst,
                        FAR const mbedtls_sha1_context *src)
{
  cryptodev_clone(dst, src);
}

void mbedtls_sha1_init(FAR mbedtls_sha1_context *ctx)
{
  cryptodev_init(ctx);
}

void mbedtls_sha1_free(FAR mbedtls_sha1_context *ctx)
{
  cryptodev_free(ctx);
}

int mbedtls_sha1_starts(FAR mbedtls_sha1_context *ctx)
{
  ctx->session.mac = CRYPTO_SHA1;
  if (cryptodev_get_session(ctx) != 0)
    {
      return MBEDTLS_ERR_SHA1_BAD_INPUT_DATA;
    }

  return 0;
}

int mbedtls_sha1_update(FAR mbedtls_sha1_context *ctx,
                        FAR const unsigned char *input,
                        size_t ilen)
{
  ctx->crypt.op = COP_ENCRYPT;
  ctx->crypt.flags |= COP_FLAG_UPDATE;
  ctx->crypt.src = (caddr_t)input;
  ctx->crypt.len = ilen;
  if (cryptodev_crypt(ctx) != 0)
    {
      return MBEDTLS_ERR_SHA1_BAD_INPUT_DATA;
    }

  return 0;
}

int mbedtls_sha1_finish(FAR mbedtls_sha1_context *ctx,
                        unsigned char output[20])
{
  int ret;

  ctx->crypt.op = COP_ENCRYPT;
  ctx->crypt.flags = 0;
  ctx->crypt.mac = (caddr_t)output;
  ret = cryptodev_crypt(ctx);
  if (ret != 0)
    {
      ret = MBEDTLS_ERR_SHA1_BAD_INPUT_DATA;
    }

  cryptodev_free_session(ctx);
  return ret;
}
