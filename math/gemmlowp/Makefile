############################################################################
# apps/math/gemmlowp/Makefile
#
# SPDX-License-Identifier: Apache-2.0
#
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.  The
# ASF licenses this file to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance with the
# License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations
# under the License.
#
############################################################################

include $(APPDIR)/Make.defs

MODULE = $(CONFIG_MATH_GEMMLOWP)

GEMMLOWP_VER = 719139ce755a0f31cbf1c37f7f98adcc7fc9f425

gemmlowp.zip:
	$(Q) curl -L https://github.com/google/gemmlowp/archive/$(GEMMLOWP_VER).zip -o gemmlowp.zip
	$(Q) unzip -o gemmlowp.zip
	$(Q) mv gemmlowp-$(GEMMLOWP_VER) gemmlowp

# Download and unpack tarball if no git repo found
ifeq ($(wildcard gemmlowp/.git),)
context:: gemmlowp.zip

distclean::
	$(call DELDIR, gemmlowp)
	$(call DELFILE, gemmlowp.zip)
endif

include $(APPDIR)/Application.mk
