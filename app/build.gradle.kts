val NDK_VERSION by extra(project.properties["NDK_VERSION"] as? String ?: "26.1.10909125")
val ARCH_ABI by extra(project.properties["ARCH_ABI"] as? String ?: "arm64-v8a")
val MIN_SDK by extra((project.properties["MIN_SDK"] as? String ?: "21").toInt())
val TARGET_SDK by extra((project.properties["TARGET_SDK"] as? String ?: "33").toInt())
val STL_TYPE by extra(project.properties["STL_TYPE"] as? String ?: "c++_shared")
val SFML_STATIC by extra(project.properties["SFML_STATIC"] as? String ?: "FALSE")

plugins {
    id("com.android.application")
}

fun getEnv(key: String): String {
    val envFile = file(".env")
    if (envFile.exists()) {
        val envs = envFile.readLines().associate { 
            val (key, value) = it.split("=")
            key to value 
        }
        return envs[key] ?: ""
    }
    return ""
}

android {
    namespace = "org.sfmldev.android"
    ndkVersion = NDK_VERSION
    compileSdk = TARGET_SDK
    defaultConfig {
        applicationId = "org.sfmldev.android"
        minSdk = MIN_SDK
        targetSdk = TARGET_SDK
        versionCode = 1
        versionName = "1.0"
        ndk {
            abiFilters.add(ARCH_ABI)
        }
        externalNativeBuild {
            cmake {
                arguments.add("-DANDROID_STL=${STL_TYPE}")
                arguments.add("-DSFML_STATIC_LIBRARIES=${SFML_STATIC}")
            }
        }
    }
    signingConfigs {
        create("release") {
            // Replace with your signing configuration details
            storeFile = file("release.keystore")
            storePassword = getEnv("STORE_PASSWORD")
            keyAlias = "sample"
            keyPassword = getEnv("KEY_PASSWORD")
        }
        // You can add other signing configurations if needed
    }
    buildTypes {
        getByName("release") {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android.txt"), "proguard-rules.pro")
            signingConfig = signingConfigs.getByName("release")
        }
    }
    externalNativeBuild {
        cmake {
            path("src/main/jni/CMakeLists.txt")
        }
    }
}

dependencies {
    implementation(fileTree(mapOf("dir" to "libs", "include" to listOf("*.jar"))))
}
