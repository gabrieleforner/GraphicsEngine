#include "core/Renderer.h"
#include "util/ConsoleLog.h"

static VKAPI_ATTR VkBool32 VKAPI_CALL engineDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void*)
{
    if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        em_printError(pCallbackData->pMessage);
    }
    else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        em_printWarning(pCallbackData->pMessage);
    }
    else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
        em_printInfo(pCallbackData->pMessage);
    }
    return VK_FALSE;
}
void Renderer::create(GLFWwindow *window)
{
    vkb::InstanceBuilder instanceBuilder;
    auto outInstance = instanceBuilder
#ifndef NDEBUG
        .request_validation_layers(true)
#else
        .request_validation_layers(false)
#endif
    .require_api_version(1, 3, 0)
    .set_app_name("FastGFX")
    .set_engine_name("FastGFX")
    .set_app_version(1, 0, 0)
    .set_engine_version(1, 0, 0)
    .set_debug_callback(engineDebugCallback)
    .build();
    if (!outInstance.has_value()) {
        printError("Failed to create VkInstance!");
        printError(outInstance.error().message().c_str());
        exit(-1);
    }
    this->instance = outInstance.value();
    this->engineInstance = this->instance.instance;
    this->engineDebugMessenger = this->instance.debug_messenger;
    printSuccess("VkInstance created successfully!");

    VkSurfaceKHR surface = VK_NULL_HANDLE;
    glfwCreateWindowSurface(this->engineInstance, window, nullptr, &surface);

    vkb::PhysicalDeviceSelector deviceSelector(this->instance);
    auto outPhysicalDevice = deviceSelector
        .set_minimum_version(1, 2)
        .set_surface(surface)
        .select();
    if (!outPhysicalDevice.has_value()) {
        printError("Failed to create VkPhysicalDevice!");
        printError(outPhysicalDevice.error().message().c_str());
        exit(-1);
    }
    this->engineSurface = surface;
    this->physicalDevice = outPhysicalDevice.value();
    this->enginePhysicalDevice = this->physicalDevice.physical_device;
    printSuccess("VkPhysicalDevice created successfully!");
    printSuccess(this->physicalDevice.name.c_str());

    vkb::DeviceBuilder deviceBuilder(this->physicalDevice);
    auto outDevice = deviceBuilder.build();
    if (!outDevice.has_value()) {
        printError("Failed to create VkDevice!");
        printError(outDevice.error().message().c_str());
        exit(-1);
    }
    this->device = outDevice.value();
    this->engineDevice = this->device.device;
    this->enginePresentQueue = outDevice->get_queue(vkb::QueueType::present).value();
    this->engineGraphicsProcQueue = outDevice->get_queue(vkb::QueueType::graphics).value();
    printSuccess("VkDevice created successfully!");

    int size[2];
    glfwGetWindowSize(window, &size[0], &size[1]);

    vkb::SwapchainBuilder scBuilder(this->device);
    auto outSwpachain = scBuilder
    .set_desired_format(VkSurfaceFormatKHR{ .format = VK_FORMAT_B8G8R8A8_UNORM,
        .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR })
    .set_desired_extent(size[0], size[1])
    .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
    .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT)
    .build();
    if (!outSwpachain.has_value()) {
        printError("Failed to create VkSwapchainKHR!");
        printError(outSwpachain.error().message().c_str());
        exit(-1);
    }
    this->swapchain = outSwpachain.value();
    this->swapChain = outSwpachain.value().swapchain;
    this->images = outSwpachain.value().get_images().value();
    this->imageViews = outSwpachain.value().get_image_views().value();
    printSuccess("VkSwapchainKHR created successfully!");

    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = this->swapchain.image_format;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;


    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.pSubpasses = &subpass;

    VkResult result;
    result = vkCreateRenderPass(this->engineDevice, &renderPassInfo, nullptr, &this->engineRenderPass);
    if (result != VK_SUCCESS) {
        printError("Failed to create render pass!");
        exit(-1);
    }
    printSuccess("VkRenderPass created successfully!");

    framebuffers.resize(this->imageViews.size());
    for (uint32_t i = 0; i < this->imageViews.size(); i++) {
        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = this->engineRenderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.width = this->swapchain.extent.width;
        framebufferInfo.height = this->swapchain.extent.height;
        framebufferInfo.layers = 1;
        framebufferInfo.pAttachments = &this->imageViews[i];

        result = vkCreateFramebuffer(this->engineDevice, &framebufferInfo, nullptr, &framebuffers[i]);
        if (result != VK_SUCCESS) {
            printError("Failed to create VkFramebuffer!");
        }
        printSuccess("VkFrameBuffer created successfully!");
    }

    VkCommandPoolCreateInfo commandPoolInfo = {};
    commandPoolInfo.queueFamilyIndex = device.get_queue_index(vkb::QueueType::graphics).value();
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    result = vkCreateCommandPool(this->engineDevice, &commandPoolInfo, nullptr, &this->commandPool);
    if (result != VK_SUCCESS) {
        printError("Failed to create VkCommandPool!");
    }
    printSuccess("VkCommandPool created successfully!");

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;
    result = vkAllocateCommandBuffers(this->engineDevice, &allocInfo, &this->commandBuffer);
    if (result != VK_SUCCESS) {
        printError("Failed to create VkCommandBuffer!");
    }
    printSuccess("VkCommandBuffer created successfully!");

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
    vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS ||
    vkCreateFence(device, &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to create semaphores!");
    }
}

void Renderer::setFrame() {
    vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
    vkResetFences(device, 1, &inFlightFence);
    vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
    vkResetCommandBuffer(this->commandBuffer, 0);

    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0; // Optional
    beginInfo.pInheritanceInfo = nullptr; // Optional
    vkBeginCommandBuffer(this->commandBuffer, &beginInfo);

    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = this->engineRenderPass;
    renderPassInfo.framebuffer = framebuffers[imageIndex];
    renderPassInfo.renderArea.offset = {0 ,0};
    renderPassInfo.renderArea.extent = swapchain.extent;
}

void Renderer::startDrawRecord() {
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &this->clearColor;
    vkCmdBeginRenderPass(this->commandBuffer, &this->renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapchain.extent.width);
    viewport.height = static_cast<float>(swapchain.extent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = swapchain.extent;
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}
void Renderer::endDrawRecord() {
    vkCmdEndRenderPass(this->commandBuffer);
    vkEndCommandBuffer(this->commandBuffer);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;
    VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(this->engineGraphicsProcQueue, 1, &submitInfo, inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    vkQueuePresentKHR(this->enginePresentQueue, &presentInfo);
}
void Renderer::destroy()
{
    vkWaitForFences(device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);
    vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);
    vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
    vkDestroyFence(device, inFlightFence, nullptr);
    vkDestroyCommandPool(this->engineDevice, this->commandPool, nullptr);
    for (auto& fb : framebuffers) {
        vkDestroyFramebuffer(this->engineDevice, fb, nullptr);
    }
    vkDestroyRenderPass(this->device, this->engineRenderPass, nullptr);
    for (auto& imageView : this->imageViews) {
        vkDestroyImageView(this->engineDevice, imageView, nullptr);
    }
    vkb::destroy_swapchain(this->swapchain);
    vkb::destroy_device(this->device);
    vkb::destroy_surface(this->instance, this->engineSurface);
    vkb::destroy_debug_utils_messenger(this->engineInstance, this->engineDebugMessenger);
    vkDestroyInstance(this->engineInstance, nullptr);
    std::cout << "Goodbye!" << std::endl;
}
