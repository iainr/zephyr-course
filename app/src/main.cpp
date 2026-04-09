#include <zephyr/kernel.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

#define LED_STRIP_NODE DT_ALIAS(led_strip)
#define NUM_LEDS 1

static const struct device *strip = DEVICE_DT_GET(LED_STRIP_NODE);

static struct led_rgb colors[] = {
    { .r = 255, .g = 0,   .b = 0   },
    { .r = 0,   .g = 255, .b = 0   },
    { .r = 0,   .g = 0,   .b = 255 },
};

static const char * const color_names[] = { "Red", "Green", "Blue" };

int main(void)
{
    if (!device_is_ready(strip)) {
        LOG_ERR("LED strip device not ready");
        return -ENODEV;
    }

    LOG_INF("LED strip device ready");

    int color_selector = 0;

    while (1) {
        LOG_INF("Color: %s, sleep_ms: %d", color_names[color_selector], CONFIG_BLINK_SLEEP_MS);
        led_strip_update_rgb(strip, &colors[color_selector], NUM_LEDS);
        color_selector = (color_selector + 1) % ARRAY_SIZE(colors);
        k_msleep(CONFIG_BLINK_SLEEP_MS);
    }

    return 0;
}