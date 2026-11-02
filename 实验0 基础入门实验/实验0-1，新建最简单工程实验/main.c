/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-12-29
 * @brief       最精简STM32工程, 除了启动文件(.s文件), 未使用任何库文件
 *              该代码实现功能：通过PB5控制DS0闪烁
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20201229
 * 第一次发布
 *
 ****************************************************************************************************
 */


/* 总线基地址定义 */
#define PERIPH_BASE         0x40000000                          /* 外设基地址 */

#define APB1PERIPH_BASE     PERIPH_BASE                         /* APB1总线基地址 */
#define APB2PERIPH_BASE     (PERIPH_BASE + 0x00010000)          /* APB2总线基地址 */
#define AHBPERIPH_BASE      (PERIPH_BASE + 0x00020000)          /* AHB总线基地址 */

/* 外设基地址定义 */
#define RCC_BASE            (AHBPERIPH_BASE + 0x00001000)       /* RCC基地址 */
#define GPIOB_BASE          (APB2PERIPH_BASE + 0x00000C00)      /* GPIOB基地址 */


/* 外设相关寄存器映射(定义) */
#define RCC_APB2ENR         *(volatile unsigned int *)(RCC_BASE + 0x18)     /* RCC_APB2ENR寄存器映射 */
    
#define GPIOB_CRL           *(volatile unsigned int *)(GPIOB_BASE + 0x00)   /* GPIOB_CRL寄存器映射 */
#define GPIOB_CRH           *(volatile unsigned int *)(GPIOB_BASE + 0x04)   /* GPIOB_CRH寄存器映射 */
#define GPIOB_IDR           *(volatile unsigned int *)(GPIOB_BASE + 0x08)   /* GPIOB_IDR寄存器映射 */
#define GPIOB_ODR           *(volatile unsigned int *)(GPIOB_BASE + 0x0C)   /* GPIOB_ODR寄存器映射 */


/* 延时函数 */
static void delay_x(volatile unsigned int t)
{
    while(t--);
}

/* main函数 */
int main(void)
{
    /* 未执行任何PLL时钟配置, 默认使用HSI(8M)工作, 相当于工作在主频8Mhz频率下 */

    RCC_APB2ENR |= 1 << 3;          /* GPIOB 时钟使能 */

    GPIOB_CRL &= ~(0X0FUL << 20);   /* MODE5[1:0], CNF5[1:0], 清零 */
    GPIOB_CRL |= 0x03 << 20;        /* MODE5[1:0]=3, PB5输出模式, 速度50Mhz */
    GPIOB_CRL |= 0x00 << 22;        /* CNF5[1:0] =0, PB5推挽输出模式 */

    while(1)
    {
        GPIOB_ODR |= 1 << 5;        /* PB5 = 1, LED0灭 */
        delay_x(500000);            /* 延时一定时间 */
        GPIOB_ODR &= ~(1UL << 5);   /* PB5 = 0, LED0亮 */
        delay_x(500000);            /* 延时一定时间 */
    }
}
























