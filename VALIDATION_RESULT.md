# Saga 0.17.0 — live external validation evidence

Date: 2026-08-09

This repository contains evidence produced on external GitHub-hosted targets and a public Internet registry endpoint. CI/virtual hardware evidence is deliberately distinguished from physical-hardware and organizationally independent evidence.

## Externally executed and passed

- **Windows Direct3D 11 API path:** PASS on GitHub-hosted Windows Server 2025. D3D11 device creation executed successfully. The exposed adapter was Microsoft Basic Render Driver, so this is not a physical-GPU claim.
- **macOS Metal API path:** PASS on GitHub-hosted macOS arm64. Metal device, command queue, RGBA8 texture and command buffer executed successfully. The device was Apple Paravirtual, so this is not a physical-Mac/GPU claim.
- **Vulkan ICD + surface/present path:** PASS on an external Ubuntu runner after installing Mesa Vulkan ICD. `vulkaninfo` exposed `VK_KHR_surface`/Xlib surface and `vkcube` selected llvmpipe. This validates a real Vulkan ICD/WSI/present software path, not a physical GPU.
- **Internet package registry:** PASS. A separate runner fetched the signed static registry over public HTTPS and verified the index plus both starter-package SHA-256 values.

## Attempted, not passed

- **Saga Native CLI build/run on Windows and macOS:** attempted on both target runners. The jobs stopped before compilation because the connector-mediated large base64 source-transfer artifact was truncated. This is a distribution-transfer failure, not evidence of a Saga compiler/runtime defect, and therefore it is not marked PASS.

## External prerequisites still unavailable

- physical Windows/macOS/Vulkan GPU execution;
- physical USB/Bluetooth gamepad passthrough;
- a complete second implementation governed by an organization independent of the Saga project;
- a signed certificate issued by an independent third-party conformance laboratory.

These items must not be self-certified. Public issues in this repository are used to recruit genuinely independent hardware executors, implementers and labs.

## Public registry

Convenience endpoint:

`https://raw.githubusercontent.com/Naokibot/dev_1/main/registry/index.json`

For reproducible consumption, prefer a commit-pinned raw URL rather than `main`.
