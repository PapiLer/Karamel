/*
 *
 * FocalTech TouchScreen driver.
 *
<<<<<<< HEAD
 * Copyright (c) 2012-2019, FocalTech Systems, Ltd., all rights reserved.
=======
 * Copyright (c) 2012-2018, FocalTech Systems, Ltd., all rights reserved.
 * Copyright (C) 2020 XiaoMi, Inc.
>>>>>>> 7ccad13b16fa (drivers: input: Import FTS touchscreen driver and its minimal changes from Xiaomi)
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/************************************************************************
*
* File Name: focaltech_i2c.c
*
* Author: Focaltech Driver Team
*
* Created: 2016-08-04
*
* Abstract: i2c communication with TP
*
* Version: v1.0
*
* Revision History:
*
************************************************************************/

/*****************************************************************************
* Included header files
*****************************************************************************/
#include "focaltech_core.h"

/*****************************************************************************
* Private constant and macro definitions using #define
*****************************************************************************/
<<<<<<< HEAD
#define I2C_RETRY_NUMBER                    3
#define I2C_BUF_LENGTH                      256

/*****************************************************************************
* Private enumerations, structures and unions using typedef
*****************************************************************************/

/*****************************************************************************
* Static variables
*****************************************************************************/
=======
#define I2C_RETRY_NUMBER        3
/*****************************************************************************
* Private enumerations, structures and unions using typedef
*****************************************************************************/

/*****************************************************************************
* Static variables
*****************************************************************************/
static DEFINE_MUTEX(i2c_rw_access);
>>>>>>> 7ccad13b16fa (drivers: input: Import FTS touchscreen driver and its minimal changes from Xiaomi)

/*****************************************************************************
* Global variable or extern global variabls/functions
*****************************************************************************/

/*****************************************************************************
* Static function prototypes
*****************************************************************************/

/*****************************************************************************
* functions body
*****************************************************************************/
<<<<<<< HEAD
int fts_read(u8 *cmd, u32 cmdlen, u8 *data, u32 datalen)
{
	int ret = 0;
	int i = 0;
	struct fts_ts_data *ts_data = fts_data;
	struct i2c_msg msg_list[2];
	struct i2c_msg *msg = NULL;
	int msg_num = 0;
=======

/************************************************************************
* Name: fts_i2c_read
* Brief: i2c read
* Input: i2c info, write buf, write len, read buf, read len
* Output: get data in the 3rd buf
* Return: fail <0
***********************************************************************/
int fts_i2c_read(struct i2c_client *client, char *writebuf, int writelen, char *readbuf, int readlen)
{
	int ret = 0;
	int i = 0;
>>>>>>> 7ccad13b16fa (drivers: input: Import FTS touchscreen driver and its minimal changes from Xiaomi)

	/* must have data when read */
	if (!ts_data || !ts_data->client || !data || !datalen
		|| (datalen >= I2C_BUF_LENGTH) || (cmdlen >= I2C_BUF_LENGTH)) {
		FTS_ERROR("fts_data/client/cmdlen(%d)/data/datalen(%d) is invalid",
			cmdlen, datalen);
		return -EINVAL;
	}

<<<<<<< HEAD
	mutex_lock(&ts_data->bus_lock);
	memset(&msg_list[0], 0, sizeof(struct i2c_msg));
	memset(&msg_list[1], 0, sizeof(struct i2c_msg));
	memcpy(ts_data->bus_tx_buf, cmd, cmdlen);
	msg_list[0].addr = ts_data->client->addr;
	msg_list[0].flags = 0;
	msg_list[0].len = cmdlen;
	msg_list[0].buf = ts_data->bus_tx_buf;
	msg_list[1].addr = ts_data->client->addr;
	msg_list[1].flags = I2C_M_RD;
	msg_list[1].len = datalen;
	msg_list[1].buf = ts_data->bus_rx_buf;
	if (cmd && cmdlen) {
		msg = &msg_list[0];
		msg_num = 2;
	} else {
		msg = &msg_list[1];
		msg_num = 1;
	}

	for (i = 0; i < I2C_RETRY_NUMBER; i++) {
		ret = i2c_transfer(ts_data->client->adapter, msg, msg_num);
		if (ret < 0) {
			FTS_ERROR("i2c_transfer(read) fail,ret:%d", ret);
		} else {
			memcpy(data, ts_data->bus_rx_buf, datalen);
			break;
		}
	}

	mutex_unlock(&ts_data->bus_lock);
	return ret;
}

int fts_write(u8 *writebuf, u32 writelen)
{
	int ret = 0;
	int i = 0;
	struct fts_ts_data *ts_data = fts_data;
	struct i2c_msg msgs;

	if (!ts_data || !ts_data->client || !writebuf || !writelen
		|| (writelen >= I2C_BUF_LENGTH)) {
		FTS_ERROR("fts_data/client/data/datalen(%d) is invalid", writelen);
		return -EINVAL;
	}

	mutex_lock(&ts_data->bus_lock);
	memset(&msgs, 0, sizeof(struct i2c_msg));
	memcpy(ts_data->bus_tx_buf, writebuf, writelen);
	msgs.addr = ts_data->client->addr;
	msgs.flags = 0;
	msgs.len = writelen;
	msgs.buf = ts_data->bus_tx_buf;
	for (i = 0; i < I2C_RETRY_NUMBER; i++) {
		ret = i2c_transfer(ts_data->client->adapter, &msgs, 1);
		if (ret < 0) {
			FTS_ERROR("i2c_transfer(write) fail,ret:%d", ret);
		} else {
			break;
		}
	}
	mutex_unlock(&ts_data->bus_lock);
	return ret;
}

int fts_read_reg(u8 addr, u8 *value)
=======
	if (readlen > 0) {
		if (writelen > 0) {
			struct i2c_msg msgs[] = {
				{
					.addr = client->addr,
					.flags = 0,
					.len = writelen,
					.buf = writebuf,
				},
				{
					.addr = client->addr,
					.flags = I2C_M_RD,
					.len = readlen,
					.buf = readbuf,
				},
			};
			for (i = 0; i < I2C_RETRY_NUMBER; i++) {
				ret = i2c_transfer(client->adapter, msgs, 2);
				if (ret < 0) {
					FTS_ERROR("[IIC]: i2c_transfer(write) error, ret=%d!!", ret);
				} else
					break;
			}
		} else {
			struct i2c_msg msgs[] = {
				{
					.addr = client->addr,
					.flags = I2C_M_RD,
					.len = readlen,
					.buf = readbuf,
				},
			};
			for (i = 0; i < I2C_RETRY_NUMBER; i++) {
				ret = i2c_transfer(client->adapter, msgs, 1);
				if (ret < 0) {
					FTS_ERROR("[IIC]: i2c_transfer(read) error, ret=%d!!", ret);
				} else
					break;
			}
		}
	}

	mutex_unlock(&i2c_rw_access);
	return ret;
}

/************************************************************************
* Name: fts_i2c_write
* Brief: i2c write
* Input: i2c info, write buf, write len
* Output: no
* Return: fail <0
***********************************************************************/
int fts_i2c_write(struct i2c_client *client, char *writebuf, int writelen)
{
	int ret = 0;
	int i = 0;

	mutex_lock(&i2c_rw_access);
	if (writelen > 0) {
		struct i2c_msg msgs[] = {
			{
				.addr = client->addr,
				.flags = 0,
				.len = writelen,
				.buf = writebuf,
			},
		};
		for (i = 0; i < I2C_RETRY_NUMBER; i++) {
			ret = i2c_transfer(client->adapter, msgs, 1);
			if (ret < 0) {
				FTS_ERROR("%s: i2c_transfer(write) error, ret=%d", __func__, ret);
			} else
				break;
		}
	}
	mutex_unlock(&i2c_rw_access);

	return ret;
}

/************************************************************************
* Name: fts_i2c_write_reg
* Brief: write register
* Input: i2c info, reg address, reg value
* Output: no
* Return: fail <0
***********************************************************************/
int fts_i2c_write_reg(struct i2c_client *client, u8 regaddr, u8 regvalue)
>>>>>>> 7ccad13b16fa (drivers: input: Import FTS touchscreen driver and its minimal changes from Xiaomi)
{
	return fts_read(&addr, 1, value, 1);
}

<<<<<<< HEAD
int fts_write_reg(u8 addr, u8 value)
=======
/************************************************************************
* Name: fts_i2c_read_reg
* Brief: read register
* Input: i2c info, reg address, reg value
* Output: get reg value
* Return: fail <0
***********************************************************************/
int fts_i2c_read_reg(struct i2c_client *client, u8 regaddr, u8 *regvalue)
>>>>>>> 7ccad13b16fa (drivers: input: Import FTS touchscreen driver and its minimal changes from Xiaomi)
{
	u8 buf[2] = { 0 };

	buf[0] = addr;
	buf[1] = value;
	return fts_write(buf, sizeof(buf));
}

<<<<<<< HEAD
int fts_bus_init(struct fts_ts_data *ts_data)
=======
/************************************************************************
* HID to standard I2C
***********************************************************************/
int fts_i2c_hid2std(struct i2c_client *client)
{
	int ret = 0;
	u8 buf[3] = {0xeb, 0xaa, 0x09};

	ret = fts_i2c_write(client, buf, 3);
	if (ret < 0)
		FTS_ERROR("hid2std cmd write fail");
	else {
		msleep(10);
		buf[0] = buf[1] = buf[2] = 0;
		ret = fts_i2c_read(client, NULL, 0, buf, 3);
		if (ret < 0)
			FTS_ERROR("hid2std cmd read fail");
		else if ((0xeb == buf[0]) && (0xaa == buf[1]) && (0x08 == buf[2])) {
			FTS_DEBUG("hidi2c change to stdi2c successful");
		} else {
			FTS_ERROR("hidi2c change to stdi2c fail");
		}
	}
	return ret;
}

/************************************************************************
* Name: fts_i2c_init
* Brief: fts i2c init
* Input:
* Output:
* Return:
***********************************************************************/
int fts_i2c_init(void)
{
	FTS_FUNC_ENTER();

	FTS_FUNC_EXIT();
	return 0;
}
/************************************************************************
* Name: fts_i2c_exit
* Brief: fts i2c exit
* Input:
* Output:
* Return:
***********************************************************************/
int fts_i2c_exit(void)
>>>>>>> 7ccad13b16fa (drivers: input: Import FTS touchscreen driver and its minimal changes from Xiaomi)
{
	FTS_FUNC_ENTER();
	ts_data->bus_tx_buf = kzalloc(I2C_BUF_LENGTH, GFP_KERNEL);
	if (NULL == ts_data->bus_tx_buf) {
		FTS_ERROR("failed to allocate memory for bus_tx_buf");
		return -ENOMEM;
	}

	ts_data->bus_rx_buf = kzalloc(I2C_BUF_LENGTH, GFP_KERNEL);
	if (NULL == ts_data->bus_rx_buf) {
		FTS_ERROR("failed to allocate memory for bus_rx_buf");
		return -ENOMEM;
	}
	FTS_FUNC_EXIT();
	return 0;
}

int fts_bus_exit(struct fts_ts_data *ts_data)
{
	FTS_FUNC_ENTER();
	if (ts_data && ts_data->bus_tx_buf) {
		kfree(ts_data->bus_tx_buf);
		ts_data->bus_tx_buf = NULL;
	}

	if (ts_data && ts_data->bus_rx_buf) {
		kfree(ts_data->bus_rx_buf);
		ts_data->bus_rx_buf = NULL;
	}
	FTS_FUNC_EXIT();
	return 0;
}