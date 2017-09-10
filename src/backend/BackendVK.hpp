#ifndef BACKENDVK_DEF
#define BACKENDVK_DEF

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <vulkan/vulkan.hpp>
#include <unistd.h>

#include <Base.hpp>

class BackendVK : public BackendBase{
public:
	BackendVK();
	~BackendVK();
	void run();
private:
	VkInstance vkInstance;
	VkDevice vkDevice;
	VkSurfaceKHR vkSurface;
	VkQueue vkGraphicsQueue;
	VkQueue vkPresentQueue;
	VkSwapchainKHR vkSwapChain;
	VkRenderPass vkRenderPass;
	VkPipelineLayout vkPipelineLayout;
	VkPipeline vkGraphicsPipeline;
	VkCommandPool vkCommandPool;
	VkSemaphore vkImageAvailableSemaphore;
	VkSemaphore vkRenderFinishedSemaphore;
	std::vector<VkImage> vkSwapChainImages;
	std::vector<VkImageView> vkSwapChainImageViews;
	std::vector<VkFramebuffer> vkSwapChainFramebuffers;
	std::vector<VkCommandBuffer> vkCommandBuffers;

	VkShaderModule createShaderModule(const char *fileName);
};

#endif