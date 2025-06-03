#pragma once

#define GLFW_INCLUDE_VULKAN
#define GLM_ENABLE_EXPERIMENTAL
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <vector>
#include <optional>
#include <set>
#include <cstdint>      // for UINT32_MAX
#include <limits>       // for std::numeric_limits
#include <fstream>
#include <algorithm>
#include <array>

// Dimensione finestra
const uint32_t WIDTH = 600;
const uint32_t HEIGHT = 600;

// Path ai due shader SPIR-V (assicurati che esistano o modifica i path)
const std::string VERT_SHADER_PATH = "shaders/basic.vert.spv";
const std::string FRAG_SHADER_PATH = "shaders/basic.frag.spv";

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

// Funzione di callback per il debug messenger (se abilitati i validation layers)
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT       messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT              messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData)
{
    std::cerr << "[VULKAN] " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}

// Nome del layer di validazione (se abilitato)
const std::vector<const char*> validationLayers =
{
    "VK_LAYER_KHRONOS_validation"
};

std::vector<const char*> getRequiredExtensions();
bool checkValidationLayerSupport();
VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger);
void DestroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator);

struct QueueFamilyIndices
{
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};
struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR        capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR>   presentModes;
};
struct Buffer
{
    VkBuffer       handle = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    VkDeviceSize   size = 0;
    VkBufferUsageFlagBits usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
};
struct Vertex
{
    glm::vec2 pos;
    glm::vec2 uv;
    glm::u8vec4 col; // oppure uint32_t se vuoi compatibilità diretta
};
struct PushConstants
{
    glm::mat4 ViewProjection;
    glm::mat4 Transform;
};

class Cube
{
public:

    void run();

private:

    //-------------------------------------------------------------------------------
    // MEMBERS
    //-------------------------------------------------------------------------------
    GLFWwindow* window = nullptr;
    VkInstance                 instance = VK_NULL_HANDLE;
    VkDebugUtilsMessengerEXT   debugMessenger = VK_NULL_HANDLE;
    VkSurfaceKHR               surface = VK_NULL_HANDLE;
    VkPhysicalDevice           physicalDevice = VK_NULL_HANDLE;
    VkDevice                   device = VK_NULL_HANDLE;
    VkQueue                    graphicsQueue = VK_NULL_HANDLE;
    VkQueue                    presentQueue = VK_NULL_HANDLE;
    VkSwapchainKHR             swapChain = VK_NULL_HANDLE;
    std::vector<VkImage>       swapChainImages;
    VkFormat                   swapChainImageFormat;
    VkExtent2D                 swapChainExtent;
    std::vector<VkImageView>   swapChainImageViews;
    VkRenderPass               renderPass = VK_NULL_HANDLE;
    VkPipelineLayout           pipelineLayout = VK_NULL_HANDLE;
    VkPipeline                 graphicsPipeline = VK_NULL_HANDLE;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkCommandPool              commandPool = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> commandBuffers;
    VkSemaphore                imageAvailableSemaphore = VK_NULL_HANDLE;
    VkSemaphore                renderFinishedSemaphore = VK_NULL_HANDLE;
    std::vector<VkFence> inFlightFences;

    PushConstants pushConstants;
	Buffer vertexBuffer; // Buffer per i vertici del triangolo
	Buffer indexBuffer;  // Buffer per gli indici del triangolo

    glm::vec3 cubePosition{ 0 };
    glm::vec3 cubeRotation{ 0 };
    float rotationSpeedX = 20.0f;
    float rotationSpeedY = 15.0f;

    //-------------------------------------------------------------------------------
    // WINDOW E GLFW
    //-------------------------------------------------------------------------------
    void initWindow();

    //-------------------------------------------------------------------------------
    // INIZIALIZZAZIONE VULKAN
    //-------------------------------------------------------------------------------
    void initVulkan();

    // 1) Creazione VkInstance
    void createInstance();

    // 2) Debug Messenger
    void setupDebugMessenger();

    // 3) Creazione VkSurfaceKHR da window GLFW
    void createSurface();

    // 4) Selezione Physical Device che supporti tutto ciò di cui abbiamo bisogno
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);
    void pickPhysicalDevice();

    // 5) Creazione Device Logico e ricavare le queue
    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void createLogicalDevice();

    //-------------------------------------------------------------------------------
    // SWAPCHAIN E IMAGES
    //-------------------------------------------------------------------------------
    void createSwapChain();
    void createImageViews();

    //-------------------------------------------------------------------------------
    // RENDERPASS E PIPELINE
    //-------------------------------------------------------------------------------
    void createRenderPass();
    static std::vector<char> readFile(const std::string& filename);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    void createGraphicsPipeline();
   
    //-------------------------------------------------------------------------------
	// RESIZE INDEX & VERTEX BUFFERS 
    //-------------------------------------------------------------------------------
    uint32_t findMemoryType(VkMemoryPropertyFlags properties, uint32_t typeBits);
    void CreateOrResizeBuffer(Buffer& buffer, uint64_t newSize);
    void createBuffers();

    //-------------------------------------------------------------------------------
    // FRAMEBUFFERS
    //-------------------------------------------------------------------------------
    void createFramebuffers();

    //-------------------------------------------------------------------------------
    // COMMAND POOL E COMMAND BUFFER
    //-------------------------------------------------------------------------------
    void createCommandPool();
    void createCommandBuffers();

    //-------------------------------------------------------------------------------
    // SINCRONIZZAZIONE
    //-------------------------------------------------------------------------------
    void createSemaphores();

    //-------------------------------------------------------------------------------
    // MAIN LOOP
    //-------------------------------------------------------------------------------
    void mainLoop();
    void drawFrame();

    //-------------------------------------------------------------------------------
    // CLEANUP
    //-------------------------------------------------------------------------------
    void cleanup();
};