#include <zephyr/kernel.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/device.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);


#define NUM_LEDS DT_PROP(DT_ALIAS(rgb_led), chain_length)

static const struct device *strip = DEVICE_DT_GET(DT_ALIAS(rgb_led));

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
        LOG_INF("Color: %s, sleep_ms: %d", color_names[color_selector], CONFIG_APP_HEARTBEAT_PERIOD_MS);
        led_strip_update_rgb(strip, &colors[color_selector], NUM_LEDS);
        color_selector = (color_selector + 1) % ARRAY_SIZE(colors);
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }

    return 0;
}