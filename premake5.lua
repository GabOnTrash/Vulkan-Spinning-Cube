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
        "src/**.h",
        "src/**.cpp",
        "shaders/**"
    }

    -- Include directories
    includedirs {
        "src",
        "shaders"
    }

    -- Library directories
    libdirs {
        -- "$(VULKAN_SDK)/Lib",
        -- "path/to/glfw/lib"
    }

    postbuildcommands {
    '{COPYDIR} "%{prj.location}/shaders" "%{cfg.targetdir}/shaders"'
    }

    -- Link libraries
    links {
        "vulkan-1",
        "glfw3dll",
        "glm"
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
