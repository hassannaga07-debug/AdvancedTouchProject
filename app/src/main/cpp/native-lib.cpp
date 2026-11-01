#include <jni.h>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>
#include <android/log.h>

#define LOG_TAG "AdvancedOrganicEngine"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

class AdvancedHumanizedTouchSimulator {
private:
    std::mt19937 rng;
    std::normal_distribution<float> baseTremor{0.0f, 0.35f};
    std::uniform_real_distribution<float> microJitter{-0.2f, 0.2f};

public:
    AdvancedHumanizedTouchSimulator() {
        rng.seed(static_cast<unsigned int>(
            std::chrono::steady_clock::now().time_since_epoch().count()));
    }

    void generateAdvancedPath(float startX, float startY, float targetX, float targetY,
                              float* bufferX, float* bufferY, int steps) {
        if (steps <= 0 || bufferX == nullptr || bufferY == nullptr) return;

        float midX = (startX + targetX) / 2.0f + (microJitter(rng) * 15.0f);
        float midY = (startY + targetY) / 2.0f + (microJitter(rng) * 15.0f);

        for (int i = 0; i < steps; ++i) {
            float t = steps == 1 ? 1.0f : static_cast<float>(i) / static_cast<float>(steps - 1);
            float modifiedT = 1.0f - std::pow(1.0f - t, 3.5f);
            float u = 1.0f - modifiedT;
            float tt = modifiedT * modifiedT;
            float uu = u * u;

            float currentX = uu * startX + 2.0f * u * modifiedT * midX + tt * targetX;
            float currentY = uu * startY + 2.0f * u * modifiedT * midY + tt * targetY;

            float fatigueFactor = std::sin(t * 3.14159f);
            float tremorScale = (1.0f - modifiedT) * (0.5f + fatigueFactor * 0.5f);
            float tremorX = (baseTremor(rng) + microJitter(rng)) * tremorScale;
            float tremorY = (baseTremor(rng) + microJitter(rng)) * tremorScale;

            bufferX[i] = currentX + tremorX;
            bufferY[i] = currentY + tremorY;
        }
    }
};

static AdvancedHumanizedTouchSimulator advancedTouchEngine;

extern "C" JNIEXPORT void JNICALL
Java_com_shop_lathe_MainActivity_nativeComputeAdvancedTouch(
        JNIEnv *env, jobject,
        jfloat startX, jfloat startY,
        jfloat targetX, jfloat targetY,
        jintArray outXArray, jintArray outYArray, jint steps) {

    if (env == nullptr || outXArray == nullptr || outYArray == nullptr || steps <= 0) {
        return;
    }

    const jsize xLength = env->GetArrayLength(outXArray);
    const jsize yLength = env->GetArrayLength(outYArray);
    if (steps > xLength || steps > yLength) {
        LOGI("Output arrays are shorter than requested steps");
        return;
    }

    std::vector<float> tempX(static_cast<size_t>(steps));
    std::vector<float> tempY(static_cast<size_t>(steps));
    advancedTouchEngine.generateAdvancedPath(
            startX, startY, targetX, targetY,
            tempX.data(), tempY.data(), steps);

    std::vector<jint> resultX(static_cast<size_t>(steps));
    std::vector<jint> resultY(static_cast<size_t>(steps));
    for (int i = 0; i < steps; ++i) {
        resultX[static_cast<size_t>(i)] = static_cast<jint>(std::lround(tempX[static_cast<size_t>(i)]));
        resultY[static_cast<size_t>(i)] = static_cast<jint>(std::lround(tempY[static_cast<size_t>(i)]));
    }

    env->SetIntArrayRegion(outXArray, 0, steps, resultX.data());
    env->SetIntArrayRegion(outYArray, 0, steps, resultY.data());
}
