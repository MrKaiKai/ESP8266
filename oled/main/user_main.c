/* I2C example

 This example code is in the Public Domain (or CC0 licensed, at your option.)

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"

#include "driver/i2c.h"

#include "myiic.h"
#include "mpu6050.h"
#include "oled.h"

char *TAG = "main";

QueueHandle_t mpu_msg;
TaskHandle_t *mpu6050 = NULL;
TaskHandle_t *oled = NULL;

const unsigned char gImage_l[] = { /* 0X12,0X01,0X00,0X20,0X00,0X19, */
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x03,0x00,0x00,0xFE,0x3F,0x00,0x80,0xFF,0xFF,0x00,0xE0,0xFF,0xFF,0x03,0xF0,0x07,0xF0,0x07,0xF8,0x01,0x80,0x0F,0x78,0xF0,0x07,0x0F,0x30,0xFE,0x3F,0x04,0x00,0xFF,0x7F,0x00,0x80,0x1F,0xFC,0x00,0x80,0x07,0xF0,0x00,0x00,0x81,0x40,0x00,0x00,0xF0,0x07,0x00,0x00,0xF8,0x1F,0x00,0x00,0xF8,0x0F,0x00,0x00,0x10,0x04,0x00,0x00,0x80,0x00,0x00,
		0x00,0xC0,0x01,0x00,0x00,0xC0,0x01,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};





static void oled_task_example(void *arg)
{
	mpu_data_ mpu_data_msg;
	OLED_Init();
	OLED_Clear();

//	OLED_DrawBMP(0,0,32,4,gImage_l);

	OLED_ShowCH(0, 0, (uint8_t*) "OLED OK!");
	OLED_ShowCH(0, 2, (uint8_t*) "X:");
	OLED_ShowCH(64, 2, (uint8_t*) "Y:");
	OLED_ShowCH(0, 4, (uint8_t*) "z:");
	OLED_ShowCH(0, 6, (uint8_t*) "temp:");
	vTaskDelay(500 / portTICK_RATE_MS);
	unsigned int uxHighWaterMark = 0;
	while (1)
	{
		int err = xQueueReceive(mpu_msg, &mpu_data_msg, portMAX_DELAY);
		if (err == pdTRUE)
		{
			OLED_Float(0 + 48, 6, ((float) mpu_data_msg.temp/65536) , 3, 1, 16);
			OLED_Float(0 + 16, 2, mpu_data_msg.pitch, 3, 1, 16);
			OLED_Float(64 + 16, 2, mpu_data_msg.roll, 3, 1, 16);
			OLED_Float(0 + 16, 4, mpu_data_msg.yaw, 3, 1, 16);
		}
		vTaskDelay(1 / portTICK_RATE_MS);
		uxHighWaterMark=uxTaskGetStackHighWaterMark( oled );
		printf("oled_task_example|size = %d\r\n",uxHighWaterMark);
	}
}

static void mpu6050_task(void *arg)
{
	mpu_data_ mpu = { 0 };
	ESP_LOGI(TAG, "%d:MPU6050 init Star", __LINE__);
#if NOT_USE_DMP
	short aacx = 0, aacy = 0, aacz = 0;		//加速度传感器原始数据
	short gyrox = 0, gyroy = 0, gyroz = 0;	//陀螺仪原始数据
	MPU6050_Init();
#else
	short aac_data[3]  ={0},gyro_data[3] = {0};
	uint8_t i = 3;
	while (mpu_dmp_init() && i--)
	{
		ESP_LOGI(TAG, "MPU6050 Error");
		vTaskDelay(200);
	}
#endif
	unsigned int uxHighWaterMark = 0;
	while (1)
	{
		ESP_LOGI(TAG, "MPU6050 run");

		if (mpu_dmp_get(&mpu) == 0)
		{
#if NOT_USE_DMP
			mpu.temp = MPU_Get_Temperature();	//得到温度值
			MPU_Get_Accelerometer(&aacx, &aacy, &aacz);	//得到加速度传感器数据
			MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);	//得到陀螺仪数据
			ESP_LOGI(TAG, "------------------%3.1f ,%3.1f, %3.1f", mpu.pitch,mpu.roll, mpu.yaw);
			ESP_LOGI(TAG, "%d, %d ,%d", aacx, aacy, aacz);
			ESP_LOGI(TAG, "%d, %d, %d", gyrox, gyroy, gyroz);
			ESP_LOGI(TAG, "------------------%3.2f", ((float) mpu.temp) / 100);
#else
			mpu_get_temperature(&mpu.temp, 0);
			mpu_get_gyro_reg(gyro_data, 0);
			mpu_get_accel_reg(aac_data, 0);
//			ESP_LOGI(TAG, "------------------%3.1f ,%3.1f, %3.1f", mpu.pitch,mpu.roll, mpu.yaw);
//			ESP_LOGI(TAG, "%d, %d ,%d", aac_data[0], aac_data[1], aac_data[2]);
//			ESP_LOGI(TAG, "%d, %d, %d", gyro_data[0], gyro_data[1], gyro_data[2]);
//			ESP_LOGI(TAG, "------------------%3.2f", ((float) mpu.temp / 65535));
#endif
			uxHighWaterMark = uxTaskGetStackHighWaterMark(mpu6050);
			printf("mpu6050_task|size = %d\r\n", uxHighWaterMark);
			xQueueSend(mpu_msg, &mpu, 1000);
		}
		vTaskDelay(1);
	}
}


void app_main(void)
{
	i2c_example_master_init();

	mpu_msg = xQueueCreate(5, sizeof(mpu_data_));
	xTaskCreate(mpu6050_task, "mpu6050_task", 128 * 8, NULL, 3, mpu6050);
	xTaskCreate(oled_task_example, "oled_task_example", 128 * 5, NULL, 4, oled);

}
