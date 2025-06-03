workspace "VulkanCube"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Vulkan"

project "Vulkan"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"
    targetdir ("bin/%{cfg.buildcfg}")
    objdir ("bin-int/%{cfg.buildcfg}")

    -- Source files
    files {
        "Vulkan/**.h",
        "Vulkan/**.cpp",
        "shaders/**"
    }

    -- Include directories
    includedirs {
        "Vulkan",
        -- Add paths to GLFW, GLM, Vulkan SDK as needed, e.g.:
        -- "$(VULKAN_SDK)/Include",
        -- "path/to/glfw/include",
        -- "path/to/glm"
    }

    -- Library directories
    libdirs {
        -- "$(VULKAN_SDK)/Lib",
        -- "path/to/glfw/lib"
    }

    -- Link libraries
    links {
        "vulkan-1",
        "glfw3"
        -- Add other libraries if needed
    }

    filter "system:windows"
        systemversion "latest"
        defines { "PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        symbols "On"
        defines { "DEBUG" }

    filter "configurations:Release"
        optimize "On"
        defines { "NDEBUG" }
