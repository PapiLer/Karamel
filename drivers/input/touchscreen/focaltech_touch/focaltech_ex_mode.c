/*
 *
 * FocalTech ftxxxx TouchScreen driver.
 *
<<<<<<< HEAD
 * Copyright (c) 2012-2019, Focaltech Ltd. All rights reserved.
=======
 * Copyright (c) 2012-2018, Focaltech Ltd. All rights reserved.
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

/*****************************************************************************
*
* File Name: focaltech_ex_mode.c
*
* Author: Focaltech Driver Team
*
* Created: 2016-08-31
*
* Abstract:
*
* Reference:
*
*****************************************************************************/

/*****************************************************************************
* 1.Included header files
*****************************************************************************/
#include "focaltech_core.h"

/*****************************************************************************
* 2.Private constant and macro definitions using #define
*****************************************************************************/

/*****************************************************************************
* 3.Private enumerations, structures and unions using typedef
*****************************************************************************/
<<<<<<< HEAD
enum _ex_mode {
	MODE_GLOVE = 0,
	MODE_COVER,
	MODE_CHARGER,
	REPORT_RATE,
};

/*****************************************************************************
* 4.Static variables
*****************************************************************************/

/*****************************************************************************
* 5.Global variable or extern global variabls/functions
*****************************************************************************/

/*****************************************************************************
* 6.Static function prototypes
*******************************************************************************/
static int fts_ex_mode_switch(enum _ex_mode mode, u8 value)
{
	int ret = 0;

	switch (mode) {
	case MODE_GLOVE:
		ret = fts_write_reg(FTS_REG_GLOVE_MODE_EN, value > 0 ? 1 : 0);
		if (ret < 0)
			FTS_ERROR("MODE_GLOVE switch to %d fail", value);
		break;

	case MODE_COVER:
		ret = fts_write_reg(FTS_REG_COVER_MODE_EN, value > 0 ? 1 : 0);
		if (ret < 0)
			FTS_ERROR("MODE_COVER switch to %d fail", value);
		break;

	case MODE_CHARGER:
		ret = fts_write_reg(FTS_REG_CHARGER_MODE_EN, value > 0 ? 1 : 0);
		if (ret < 0)
			FTS_ERROR("MODE_CHARGER switch to %d fail", value);
		break;

	case REPORT_RATE:
		ret = fts_write_reg(FTS_REG_REPORT_RATE, value);
		if (ret < 0)
			FTS_ERROR("REPORT_RATE switch to %d fail", value);
		break;

	default:
		FTS_ERROR("mode(%d) unsupport", mode);
		ret = -EINVAL;
		break;
	}

	return ret;
}

static ssize_t fts_glove_mode_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	int count = 0;
	u8 val = 0;
	struct fts_ts_data *ts_data = fts_data;
	struct input_dev *input_dev = ts_data->input_dev;

	mutex_lock(&input_dev->mutex);
	fts_read_reg(FTS_REG_GLOVE_MODE_EN, &val);
	count = snprintf(buf + count, PAGE_SIZE, "Glove Mode:%s\n",
			ts_data->glove_mode ? "On" : "Off");
	count += snprintf(buf + count, PAGE_SIZE, "Glove Reg(0xC0):%d\n", val);
	mutex_unlock(&input_dev->mutex);

	return count;
}

static ssize_t fts_glove_mode_store(
	struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	struct fts_ts_data *ts_data = fts_data;
=======
struct fts_mode_flag {
	int  fts_glove_mode_flag;
	int  fts_cover_mode_flag;
	int  fts_charger_mode_flag;
};

struct fts_mode_flag g_fts_mode_flag;

/*****************************************************************************
* 4.Static variables
*****************************************************************************/

/*****************************************************************************
* 5.Global variable or extern global variabls/functions
*****************************************************************************/
int fts_enter_glove_mode(struct i2c_client *client, int mode );
int fts_enter_cover_mode(struct i2c_client *client, int mode );
int fts_enter_charger_mode(struct i2c_client *client, int mode );

/*****************************************************************************
* 6.Static function prototypes
*******************************************************************************/

#if FTS_GLOVE_EN
static ssize_t fts_touch_glove_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int count;
	u8 val;
	struct input_dev *input_dev = fts_data->input_dev;
	struct i2c_client *client = container_of(dev, struct i2c_client, dev);

	mutex_lock(&input_dev->mutex);
	fts_i2c_read_reg(client, FTS_REG_GLOVE_MODE_EN, &val);
	count = snprintf(buf, PAGE_SIZE, "Glove Mode: %s\n", g_fts_mode_flag.fts_glove_mode_flag ? "On" : "Off");
	count += snprintf(buf + count, PAGE_SIZE, "Glove Reg(0xC0) = %d\n", val);
	mutex_unlock(&input_dev->mutex);

	return count;
}

static ssize_t fts_touch_glove_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret;
	struct fts_ts_data *ts_data = fts_data;
	struct i2c_client *client;


	client = ts_data->client;
	if (FTS_SYSFS_ECHO_ON(buf)) {
		if (!g_fts_mode_flag.fts_glove_mode_flag) {
			FTS_INFO("[Mode]enter glove mode");
			ret = fts_enter_glove_mode(client, true);
			if (ret >= 0) {
				g_fts_mode_flag.fts_glove_mode_flag = true;
			}
		}
	} else if (FTS_SYSFS_ECHO_OFF(buf)) {
		if (g_fts_mode_flag.fts_glove_mode_flag) {
			FTS_INFO("[Mode]exit glove mode");
			ret = fts_enter_glove_mode(client, false);
			if (ret >= 0) {
				g_fts_mode_flag.fts_glove_mode_flag = false;
			}
		}
	}
	FTS_INFO("[Mode]glove mode status:  %d", g_fts_mode_flag.fts_glove_mode_flag);
	return count;
}

/************************************************************************
* Name: fts_enter_glove_mode
* Brief:  change glove mode
* Input:  glove mode
* Output: no
* Return: success >=0, otherwise failed
***********************************************************************/
int fts_enter_glove_mode( struct i2c_client *client, int mode)
{
	int ret = 0;
	static u8 buf_addr[2] = { 0 };
	static u8 buf_value[2] = { 0 };
	buf_addr[0] = FTS_REG_GLOVE_MODE_EN; /* glove control */

	if (mode)
		buf_value[0] = 0x01;
	else
		buf_value[0] = 0x00;

	ret = fts_i2c_write_reg( client, buf_addr[0], buf_value[0]);
	if (ret < 0) {
		FTS_ERROR("[Mode]fts_enter_glove_mode write value fail");
	}

	return ret ;

}

/* read and write glove mode
*   read example: cat  fts_touch_glove_mode---read  glove mode
*   write example:echo 01 > fts_touch_glove_mode ---write glove mode to 01
*
*/
static DEVICE_ATTR (fts_glove_mode,  S_IRUGO | S_IWUSR, fts_touch_glove_show, fts_touch_glove_store);

#endif

#if FTS_COVER_EN
static ssize_t fts_touch_cover_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int count;
	u8 val;
	struct input_dev *input_dev = fts_data->input_dev;
	struct i2c_client *client = container_of(dev, struct i2c_client, dev);

	mutex_lock(&input_dev->mutex);
	fts_i2c_read_reg(client, FTS_REG_COVER_MODE_EN, &val);
	count = snprintf(buf, PAGE_SIZE, "Cover Mode: %s\n", g_fts_mode_flag.fts_cover_mode_flag ? "On" : "Off");
	count += snprintf(buf + count, PAGE_SIZE, "Cover Reg(0xC1) = %d\n", val);
	mutex_unlock(&input_dev->mutex);

	return count;
}

static ssize_t fts_touch_cover_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret;
	struct fts_ts_data *ts_data = fts_data;
	struct i2c_client *client;
>>>>>>> 7ccad13b16fa (drivers: input: Import FTS touchscreen driver and its minimal changes from Xiaomi)

	client = ts_data->client;
	if (FTS_SYSFS_ECHO_ON(buf)) {
<<<<<<< HEAD
		if (!ts_data->glove_mode) {
			FTS_DEBUG("enter glove mode");
			ret = fts_ex_mode_switch(MODE_GLOVE, ENABLE);
			if (ret >= 0) {
				ts_data->glove_mode = ENABLE;
			}
		}
	} else if (FTS_SYSFS_ECHO_OFF(buf)) {
		if (ts_data->glove_mode) {
			FTS_DEBUG("exit glove mode");
			ret = fts_ex_mode_switch(MODE_GLOVE, DISABLE);
			if (ret >= 0) {
				ts_data->glove_mode = DISABLE;
			}
		}
	}

	FTS_DEBUG("glove mode:%d", ts_data->glove_mode);
	return count;
}


static ssize_t fts_cover_mode_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	int count = 0;
	u8 val = 0;
	struct fts_ts_data *ts_data = fts_data;
	struct input_dev *input_dev = ts_data->input_dev;

	mutex_lock(&input_dev->mutex);
	fts_read_reg(FTS_REG_COVER_MODE_EN, &val);
	count = snprintf(buf + count, PAGE_SIZE, "Cover Mode:%s\n",
			ts_data->cover_mode ? "On" : "Off");
	count += snprintf(buf + count, PAGE_SIZE, "Cover Reg(0xC1):%d\n", val);
	mutex_unlock(&input_dev->mutex);

	return count;
}

static ssize_t fts_cover_mode_store(
	struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	struct fts_ts_data *ts_data = fts_data;

	if (FTS_SYSFS_ECHO_ON(buf)) {
		if (!ts_data->cover_mode) {
			FTS_DEBUG("enter cover mode");
			ret = fts_ex_mode_switch(MODE_COVER, ENABLE);
			if (ret >= 0) {
				ts_data->cover_mode = ENABLE;
			}
		}
	} else if (FTS_SYSFS_ECHO_OFF(buf)) {
		if (ts_data->cover_mode) {
			FTS_DEBUG("exit cover mode");
			ret = fts_ex_mode_switch(MODE_COVER, DISABLE);
			if (ret >= 0) {
				ts_data->cover_mode = DISABLE;
			}
		}
	}

	FTS_DEBUG("cover mode:%d", ts_data->cover_mode);
	return count;
}

static ssize_t fts_charger_mode_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	int count = 0;
	u8 val = 0;
	struct fts_ts_data *ts_data = fts_data;
	struct input_dev *input_dev = ts_data->input_dev;

	mutex_lock(&input_dev->mutex);
	fts_read_reg(FTS_REG_CHARGER_MODE_EN, &val);
	count = snprintf(buf + count, PAGE_SIZE, "Charger Mode:%s\n",
			ts_data->charger_mode ? "On" : "Off");
	count += snprintf(buf + count, PAGE_SIZE, "Charger Reg(0x8B):%d\n", val);
	mutex_unlock(&input_dev->mutex);

	return count;
}

static ssize_t fts_charger_mode_store(
	struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	struct fts_ts_data *ts_data = fts_data;

	if (FTS_SYSFS_ECHO_ON(buf)) {
		if (!ts_data->charger_mode) {
			FTS_DEBUG("enter charger mode");
			ret = fts_ex_mode_switch(MODE_CHARGER, ENABLE);
			if (ret >= 0) {
				ts_data->charger_mode = ENABLE;
			}
		}
	} else if (FTS_SYSFS_ECHO_OFF(buf)) {
		if (ts_data->charger_mode) {
			FTS_DEBUG("exit charger mode");
			ret = fts_ex_mode_switch(MODE_CHARGER, DISABLE);
			if (ret >= 0) {
				ts_data->charger_mode = DISABLE;
			}
		}
	}
=======
		if (!g_fts_mode_flag.fts_cover_mode_flag) {
			FTS_INFO("[Mode]enter cover mode");
			ret = fts_enter_cover_mode(client, true);
			if (ret >= 0) {
				g_fts_mode_flag.fts_cover_mode_flag = true;
			}
		}
	} else if (FTS_SYSFS_ECHO_OFF(buf)) {
		if (g_fts_mode_flag.fts_cover_mode_flag) {
			FTS_INFO("[Mode]exit cover mode");
			ret = fts_enter_cover_mode(client, false);
			if (ret >= 0) {
				g_fts_mode_flag.fts_cover_mode_flag = false;
			}
		}
	}
	FTS_INFO("[Mode]cover mode status:  %d", g_fts_mode_flag.fts_cover_mode_flag);
	return count;
}

/************************************************************************
* Name: fts_enter_cover_mode
* Brief:  change cover mode
* Input:  cover mode
* Output: no
* Return: success >=0, otherwise failed
***********************************************************************/
int  fts_enter_cover_mode( struct i2c_client *client, int mode)
{
	int ret = 0;
	static u8 buf_addr[2] = { 0 };
	static u8 buf_value[2] = { 0 };
	buf_addr[0] = FTS_REG_COVER_MODE_EN; /* cover control */

	if (mode)
		buf_value[0] = 0x01;
	else
		buf_value[0] = 0x00;

	ret = fts_i2c_write_reg( client, buf_addr[0], buf_value[0]);
	if (ret < 0) {
		FTS_ERROR("[Mode] fts_enter_cover_mode write value fail \n");
	}

	return ret ;

}

/* read and write cover mode
*   read example: cat  fts_touch_cover_mode---read  cover mode
*   write example:echo 01 > fts_touch_cover_mode ---write cover mode to 01
*
*/
static DEVICE_ATTR (fts_cover_mode,  S_IRUGO | S_IWUSR, fts_touch_cover_show, fts_touch_cover_store);

#endif

#if FTS_CHARGER_EN
static ssize_t fts_touch_charger_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	int count;
	u8 val;
	struct input_dev *input_dev = fts_data->input_dev;
	struct i2c_client *client = container_of(dev, struct i2c_client, dev);

	mutex_lock(&input_dev->mutex);
	fts_i2c_read_reg(client, FTS_REG_CHARGER_MODE_EN, &val);
	count = snprintf(buf, PAGE_SIZE, "Charge Mode: %s\n", g_fts_mode_flag.fts_charger_mode_flag ? "On" : "Off");
	count += snprintf(buf + count, PAGE_SIZE, "Charge Reg(0x8B) = %d\n", val);
	mutex_unlock(&input_dev->mutex);

	return count;
}

static ssize_t fts_touch_charger_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int ret;
	struct fts_ts_data *ts_data = fts_data;
	struct i2c_client *client;

	client = ts_data->client;

	if (FTS_SYSFS_ECHO_ON(buf)) {
		if (!g_fts_mode_flag.fts_charger_mode_flag) {
			FTS_INFO("[Mode]enter charger mode");
			ret = fts_enter_charger_mode(client, true);
			if (ret >= 0) {
				g_fts_mode_flag.fts_charger_mode_flag = true;
			}
		}
	} else if (FTS_SYSFS_ECHO_OFF(buf)) {
		if (g_fts_mode_flag.fts_charger_mode_flag) {
			FTS_INFO("[Mode]exit charger mode");
			ret = fts_enter_charger_mode(client, false);
			if (ret >= 0) {
				g_fts_mode_flag.fts_charger_mode_flag = false;
			}
		}
	}
	FTS_INFO("[Mode]charger mode status: %d", g_fts_mode_flag.fts_charger_mode_flag);
	return count;
}

/************************************************************************
* Name: fts_enter_charger_mode
* Brief:  change charger mode
* Input:  charger mode
* Output: no
* Return: success >=0, otherwise failed
***********************************************************************/
int  fts_enter_charger_mode(struct i2c_client *client, int mode)
{
	int ret = 0;
	static u8 buf_addr[2] = { 0 };
	static u8 buf_value[2] = { 0 };
	buf_addr[0] = FTS_REG_CHARGER_MODE_EN; /* charger control */

	if (mode)
		buf_value[0] = 0x01;
	else
		buf_value[0] = 0x00;

	ret = fts_i2c_write_reg( client, buf_addr[0], buf_value[0]);
	if (ret < 0) {
		FTS_DEBUG("[Mode]fts_enter_charger_mode write value fail");
	}

	return ret ;
>>>>>>> 7ccad13b16fa (drivers: input: Import FTS touchscreen driver and its minimal changes from Xiaomi)

	FTS_DEBUG("charger mode:%d", ts_data->glove_mode);
	return count;
}

static ssize_t fts_report_rate_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	int count = 0;
	u8 val = 0;
	struct fts_ts_data *ts_data = fts_data;
	struct input_dev *input_dev = ts_data->input_dev;

	mutex_lock(&input_dev->mutex);
	fts_read_reg(FTS_REG_REPORT_RATE, &val);
	count = scnprintf(buf + count, PAGE_SIZE, "Report Rate:%d\n",
			ts_data->report_rate);
	count += scnprintf(buf + count, PAGE_SIZE,
			"Report Rate Reg(0x88):%d\n", val);
	mutex_unlock(&input_dev->mutex);

	return count;
}

static ssize_t fts_report_rate_store(
	struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	struct fts_ts_data *ts_data = fts_data;
	int rate;

	ret = kstrtoint(buf, 16, &rate);
	if (ret)
		return ret;

	if (rate != ts_data->report_rate) {
		ret = fts_ex_mode_switch(REPORT_RATE, (u8)rate);
		if (ret >= 0)
			ts_data->report_rate = rate;
	}

	FTS_DEBUG("report rate:%d", ts_data->report_rate);
	return count;
}


/* read and write charger mode
<<<<<<< HEAD
 * read example: cat fts_glove_mode        ---read  glove mode
 * write example:echo 1 > fts_glove_mode   ---write glove mode to 01
 */
static DEVICE_ATTR(fts_glove_mode, S_IRUGO | S_IWUSR,
			fts_glove_mode_show, fts_glove_mode_store);
=======
*   read example: cat  fts_touch_charger_mode---read  charger mode
*   write example:echo 01 > fts_touch_charger_mode ---write charger mode to 01
*
*/
static DEVICE_ATTR (fts_charger_mode,  S_IRUGO | S_IWUSR, fts_touch_charger_show, fts_touch_charger_store);
>>>>>>> 7ccad13b16fa (drivers: input: Import FTS touchscreen driver and its minimal changes from Xiaomi)

static DEVICE_ATTR(fts_cover_mode, S_IRUGO | S_IWUSR,
			fts_cover_mode_show, fts_cover_mode_store);

static DEVICE_ATTR(fts_charger_mode, S_IRUGO | S_IWUSR,
			fts_charger_mode_show, fts_charger_mode_store);

static DEVICE_ATTR_RW(fts_report_rate);

static struct attribute *fts_touch_mode_attrs[] = {
	&dev_attr_fts_glove_mode.attr,
	&dev_attr_fts_cover_mode.attr,
	&dev_attr_fts_charger_mode.attr,
	&dev_attr_fts_report_rate.attr,
	NULL,
};

static struct attribute_group fts_touch_mode_group = {
	.attrs = fts_touch_mode_attrs,
};

int fts_ex_mode_recovery(struct fts_ts_data *ts_data)
{
<<<<<<< HEAD
	if (ts_data->glove_mode) {
		fts_ex_mode_switch(MODE_GLOVE, ENABLE);
	}

	if (ts_data->cover_mode) {
		fts_ex_mode_switch(MODE_COVER, ENABLE);
	}

	if (ts_data->charger_mode) {
		fts_ex_mode_switch(MODE_CHARGER, ENABLE);
	}
=======
	int err = 0;

	g_fts_mode_flag.fts_glove_mode_flag = false;
	g_fts_mode_flag.fts_cover_mode_flag = false;
	g_fts_mode_flag.fts_charger_mode_flag = false;

	err = sysfs_create_group(&client->dev.kobj, &fts_touch_mode_group);
	if (0 != err) {
		FTS_ERROR("[Mode]create sysfs failed.");
		sysfs_remove_group(&client->dev.kobj, &fts_touch_mode_group);
		return -EIO;
	} else {
		FTS_DEBUG("[Mode]create sysfs succeeded");
	}

	return err;
>>>>>>> 7ccad13b16fa (drivers: input: Import FTS touchscreen driver and its minimal changes from Xiaomi)

	if (ts_data->report_rate > 0)
		fts_ex_mode_switch(REPORT_RATE, ts_data->report_rate);

	return 0;
}

int fts_ex_mode_init(struct fts_ts_data *ts_data)
{
	int ret = 0;

	ts_data->glove_mode = DISABLE;
	ts_data->cover_mode = DISABLE;
	ts_data->charger_mode = DISABLE;
	ts_data->report_rate = 0;

	ret = sysfs_create_group(&ts_data->dev->kobj, &fts_touch_mode_group);
	if (ret < 0) {
		FTS_ERROR("create sysfs(ex_mode) fail");
		sysfs_remove_group(&ts_data->dev->kobj, &fts_touch_mode_group);
		return ret;
	} else {
		FTS_DEBUG("create sysfs(ex_mode) succeedfully");
	}

	return 0;
}

int fts_ex_mode_exit(struct fts_ts_data *ts_data)
{
	sysfs_remove_group(&ts_data->dev->kobj, &fts_touch_mode_group);
	return 0;
}
