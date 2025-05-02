#include "main.h"

auto FMC_BANK1_REG  =
    reinterpret_cast<volatile uint16_t* const>(0x60000000);

auto FMC_BANK1_DATA =
    reinterpret_cast<volatile uint16_t* const>(0x60000002);

void LCD_IO_WriteReg(const uint16_t reg) {
    *FMC_BANK1_REG = reg;
}

void LCD_IO_WriteData(const uint16_t data) {
    *FMC_BANK1_DATA = data;
}

void LCD_IO_Write(
    const uint16_t reg,
    const uint16_t data
) {
    LCD_IO_WriteReg(reg);
    LCD_IO_WriteData(data);
}

void LCD_IO_WriteMultipleData(const uint16_t* data, const uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        LCD_IO_WriteData(data[i]);
    }
}

void LCD_IO_Init() {
    LCD_IO_WriteReg(0xf000);
    LCD_IO_WriteData(0x55);
    LCD_IO_WriteReg(0xf001);
    LCD_IO_WriteData(0xaa);
    LCD_IO_WriteReg(0xf002);
    LCD_IO_WriteData(0x52);
    LCD_IO_WriteReg(0xf003);
    LCD_IO_WriteData(0x08);
    LCD_IO_WriteReg(0xf004);
    LCD_IO_WriteData(0x01);
    //# avdd: manual); LCD_IO_WriteData(
    LCD_IO_WriteReg(0xb600);
    LCD_IO_WriteData(0x34);
    LCD_IO_WriteReg(0xb601);
    LCD_IO_WriteData(0x34);
    LCD_IO_WriteReg(0xb602);
    LCD_IO_WriteData(0x34);

    LCD_IO_WriteReg(0xb000);
    LCD_IO_WriteData(0x0d);//09
    LCD_IO_WriteReg(0xb001);
    LCD_IO_WriteData(0x0d);
    LCD_IO_WriteReg(0xb002);
    LCD_IO_WriteData(0x0d);
    //# avee: manual); LCD_IO_WriteData( -6v
    LCD_IO_WriteReg(0xb700);
    LCD_IO_WriteData(0x24);
    LCD_IO_WriteReg(0xb701);
    LCD_IO_WriteData(0x24);
    LCD_IO_WriteReg(0xb702);
    LCD_IO_WriteData(0x24);

    LCD_IO_WriteReg(0xb100);
    LCD_IO_WriteData(0x0d);
    LCD_IO_WriteReg(0xb101);
    LCD_IO_WriteData(0x0d);
    LCD_IO_WriteReg(0xb102);
    LCD_IO_WriteData(0x0d);
    //#power control for
    //vcl
    LCD_IO_WriteReg(0xb800);
    LCD_IO_WriteData(0x24);
    LCD_IO_WriteReg(0xb801);
    LCD_IO_WriteData(0x24);
    LCD_IO_WriteReg(0xb802);
    LCD_IO_WriteData(0x24);

    LCD_IO_WriteReg(0xb200);
    LCD_IO_WriteData(0x00);

    //# vgh: clamp enable); LCD_IO_WriteData(
    LCD_IO_WriteReg(0xb900);
    LCD_IO_WriteData(0x24);
    LCD_IO_WriteReg(0xb901);
    LCD_IO_WriteData(0x24);
    LCD_IO_WriteReg(0xb902);
    LCD_IO_WriteData(0x24);

    LCD_IO_WriteReg(0xb300);
    LCD_IO_WriteData(0x05);
    LCD_IO_WriteReg(0xb301);
    LCD_IO_WriteData(0x05);
    LCD_IO_WriteReg(0xb302);
    LCD_IO_WriteData(0x05);

    ///LCD_IO_WriteReg(0xbf00); LCD_IO_WriteData(0x01);

    //# vgl(lvgl):
    LCD_IO_WriteReg(0xba00);
    LCD_IO_WriteData(0x34);
    LCD_IO_WriteReg(0xba01);
    LCD_IO_WriteData(0x34);
    LCD_IO_WriteReg(0xba02);
    LCD_IO_WriteData(0x34);
    //# vgl_reg(vglo)
    LCD_IO_WriteReg(0xb500);
    LCD_IO_WriteData(0x0b);
    LCD_IO_WriteReg(0xb501);
    LCD_IO_WriteData(0x0b);
    LCD_IO_WriteReg(0xb502);
    LCD_IO_WriteData(0x0b);
    //# vgmp/vgsp:
    LCD_IO_WriteReg(0xbc00);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xbc01);
    LCD_IO_WriteData(0xa3);
    LCD_IO_WriteReg(0xbc02);
    LCD_IO_WriteData(0x00);
    //# vgmn/vgsn
    LCD_IO_WriteReg(0xbd00);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xbd01);
    LCD_IO_WriteData(0xa3);
    LCD_IO_WriteReg(0xbd02);
    LCD_IO_WriteData(0x00);
    //# vcom=-0.1
    LCD_IO_WriteReg(0xbe00);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xbe01);
    LCD_IO_WriteData(0x63);//4f
    //  vcomh+0x01;
    //#r+
    LCD_IO_WriteReg(0xd100);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd101);
    LCD_IO_WriteData(0x37);
    LCD_IO_WriteReg(0xd102);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd103);
    LCD_IO_WriteData(0x52);
    LCD_IO_WriteReg(0xd104);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd105);
    LCD_IO_WriteData(0x7b);
    LCD_IO_WriteReg(0xd106);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd107);
    LCD_IO_WriteData(0x99);
    LCD_IO_WriteReg(0xd108);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd109);
    LCD_IO_WriteData(0xb1);
    LCD_IO_WriteReg(0xd10a);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd10b);
    LCD_IO_WriteData(0xd2);
    LCD_IO_WriteReg(0xd10c);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd10d);
    LCD_IO_WriteData(0xf6);
    LCD_IO_WriteReg(0xd10e);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd10f);
    LCD_IO_WriteData(0x27);
    LCD_IO_WriteReg(0xd110);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd111);
    LCD_IO_WriteData(0x4e);
    LCD_IO_WriteReg(0xd112);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd113);
    LCD_IO_WriteData(0x8c);
    LCD_IO_WriteReg(0xd114);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd115);
    LCD_IO_WriteData(0xbe);
    LCD_IO_WriteReg(0xd116);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd117);
    LCD_IO_WriteData(0x0b);
    LCD_IO_WriteReg(0xd118);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd119);
    LCD_IO_WriteData(0x48);
    LCD_IO_WriteReg(0xd11a);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd11b);
    LCD_IO_WriteData(0x4a);
    LCD_IO_WriteReg(0xd11c);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd11d);
    LCD_IO_WriteData(0x7e);
    LCD_IO_WriteReg(0xd11e);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd11f);
    LCD_IO_WriteData(0xbc);
    LCD_IO_WriteReg(0xd120);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd121);
    LCD_IO_WriteData(0xe1);
    LCD_IO_WriteReg(0xd122);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd123);
    LCD_IO_WriteData(0x10);
    LCD_IO_WriteReg(0xd124);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd125);
    LCD_IO_WriteData(0x31);
    LCD_IO_WriteReg(0xd126);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd127);
    LCD_IO_WriteData(0x5a);
    LCD_IO_WriteReg(0xd128);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd129);
    LCD_IO_WriteData(0x73);
    LCD_IO_WriteReg(0xd12a);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd12b);
    LCD_IO_WriteData(0x94);
    LCD_IO_WriteReg(0xd12c);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd12d);
    LCD_IO_WriteData(0x9f);
    LCD_IO_WriteReg(0xd12e);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd12f);
    LCD_IO_WriteData(0xb3);
    LCD_IO_WriteReg(0xd130);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd131);
    LCD_IO_WriteData(0xb9);
    LCD_IO_WriteReg(0xd132);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd133);
    LCD_IO_WriteData(0xc1);
    //#g+
    LCD_IO_WriteReg(0xd200);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd201);
    LCD_IO_WriteData(0x37);
    LCD_IO_WriteReg(0xd202);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd203);
    LCD_IO_WriteData(0x52);
    LCD_IO_WriteReg(0xd204);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd205);
    LCD_IO_WriteData(0x7b);
    LCD_IO_WriteReg(0xd206);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd207);
    LCD_IO_WriteData(0x99);
    LCD_IO_WriteReg(0xd208);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd209);
    LCD_IO_WriteData(0xb1);
    LCD_IO_WriteReg(0xd20a);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd20b);
    LCD_IO_WriteData(0xd2);
    LCD_IO_WriteReg(0xd20c);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd20d);
    LCD_IO_WriteData(0xf6);
    LCD_IO_WriteReg(0xd20e);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd20f);
    LCD_IO_WriteData(0x27);
    LCD_IO_WriteReg(0xd210);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd211);
    LCD_IO_WriteData(0x4e);
    LCD_IO_WriteReg(0xd212);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd213);
    LCD_IO_WriteData(0x8c);
    LCD_IO_WriteReg(0xd214);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd215);
    LCD_IO_WriteData(0xbe);
    LCD_IO_WriteReg(0xd216);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd217);
    LCD_IO_WriteData(0x0b);
    LCD_IO_WriteReg(0xd218);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd219);
    LCD_IO_WriteData(0x48);
    LCD_IO_WriteReg(0xd21a);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd21b);
    LCD_IO_WriteData(0x4a);
    LCD_IO_WriteReg(0xd21c);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd21d);
    LCD_IO_WriteData(0x7e);
    LCD_IO_WriteReg(0xd21e);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd21f);
    LCD_IO_WriteData(0xbc);
    LCD_IO_WriteReg(0xd220);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd221);
    LCD_IO_WriteData(0xe1);
    LCD_IO_WriteReg(0xd222);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd223);
    LCD_IO_WriteData(0x10);
    LCD_IO_WriteReg(0xd224);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd225);
    LCD_IO_WriteData(0x31);
    LCD_IO_WriteReg(0xd226);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd227);
    LCD_IO_WriteData(0x5a);
    LCD_IO_WriteReg(0xd228);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd229);
    LCD_IO_WriteData(0x73);
    LCD_IO_WriteReg(0xd22a);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd22b);
    LCD_IO_WriteData(0x94);
    LCD_IO_WriteReg(0xd22c);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd22d);
    LCD_IO_WriteData(0x9f);
    LCD_IO_WriteReg(0xd22e);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd22f);
    LCD_IO_WriteData(0xb3);
    LCD_IO_WriteReg(0xd230);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd231);
    LCD_IO_WriteData(0xb9);
    LCD_IO_WriteReg(0xd232);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd233);
    LCD_IO_WriteData(0xc1);
    //#b+
    LCD_IO_WriteReg(0xd300);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd301);
    LCD_IO_WriteData(0x37);
    LCD_IO_WriteReg(0xd302);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd303);
    LCD_IO_WriteData(0x52);
    LCD_IO_WriteReg(0xd304);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd305);
    LCD_IO_WriteData(0x7b);
    LCD_IO_WriteReg(0xd306);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd307);
    LCD_IO_WriteData(0x99);
    LCD_IO_WriteReg(0xd308);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd309);
    LCD_IO_WriteData(0xb1);
    LCD_IO_WriteReg(0xd30a);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd30b);
    LCD_IO_WriteData(0xd2);
    LCD_IO_WriteReg(0xd30c);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd30d);
    LCD_IO_WriteData(0xf6);
    LCD_IO_WriteReg(0xd30e);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd30f);
    LCD_IO_WriteData(0x27);
    LCD_IO_WriteReg(0xd310);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd311);
    LCD_IO_WriteData(0x4e);
    LCD_IO_WriteReg(0xd312);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd313);
    LCD_IO_WriteData(0x8c);
    LCD_IO_WriteReg(0xd314);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd315);
    LCD_IO_WriteData(0xbe);
    LCD_IO_WriteReg(0xd316);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd317);
    LCD_IO_WriteData(0x0b);
    LCD_IO_WriteReg(0xd318);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd319);
    LCD_IO_WriteData(0x48);
    LCD_IO_WriteReg(0xd31a);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd31b);
    LCD_IO_WriteData(0x4a);
    LCD_IO_WriteReg(0xd31c);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd31d);
    LCD_IO_WriteData(0x7e);
    LCD_IO_WriteReg(0xd31e);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd31f);
    LCD_IO_WriteData(0xbc);
    LCD_IO_WriteReg(0xd320);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd321);
    LCD_IO_WriteData(0xe1);
    LCD_IO_WriteReg(0xd322);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd323);
    LCD_IO_WriteData(0x10);
    LCD_IO_WriteReg(0xd324);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd325);
    LCD_IO_WriteData(0x31);
    LCD_IO_WriteReg(0xd326);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd327);
    LCD_IO_WriteData(0x5a);
    LCD_IO_WriteReg(0xd328);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd329);
    LCD_IO_WriteData(0x73);
    LCD_IO_WriteReg(0xd32a);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd32b);
    LCD_IO_WriteData(0x94);
    LCD_IO_WriteReg(0xd32c);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd32d);
    LCD_IO_WriteData(0x9f);
    LCD_IO_WriteReg(0xd32e);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd32f);
    LCD_IO_WriteData(0xb3);
    LCD_IO_WriteReg(0xd330);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd331);
    LCD_IO_WriteData(0xb9);
    LCD_IO_WriteReg(0xd332);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd333);
    LCD_IO_WriteData(0xc1);

    //#r-///////////////////////////////////////////
    LCD_IO_WriteReg(0xd400);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd401);
    LCD_IO_WriteData(0x37);
    LCD_IO_WriteReg(0xd402);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd403);
    LCD_IO_WriteData(0x52);
    LCD_IO_WriteReg(0xd404);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd405);
    LCD_IO_WriteData(0x7b);
    LCD_IO_WriteReg(0xd406);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd407);
    LCD_IO_WriteData(0x99);
    LCD_IO_WriteReg(0xd408);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd409);
    LCD_IO_WriteData(0xb1);
    LCD_IO_WriteReg(0xd40a);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd40b);
    LCD_IO_WriteData(0xd2);
    LCD_IO_WriteReg(0xd40c);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd40d);
    LCD_IO_WriteData(0xf6);
    LCD_IO_WriteReg(0xd40e);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd40f);
    LCD_IO_WriteData(0x27);
    LCD_IO_WriteReg(0xd410);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd411);
    LCD_IO_WriteData(0x4e);
    LCD_IO_WriteReg(0xd412);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd413);
    LCD_IO_WriteData(0x8c);
    LCD_IO_WriteReg(0xd414);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd415);
    LCD_IO_WriteData(0xbe);
    LCD_IO_WriteReg(0xd416);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd417);
    LCD_IO_WriteData(0x0b);
    LCD_IO_WriteReg(0xd418);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd419);
    LCD_IO_WriteData(0x48);
    LCD_IO_WriteReg(0xd41a);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd41b);
    LCD_IO_WriteData(0x4a);
    LCD_IO_WriteReg(0xd41c);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd41d);
    LCD_IO_WriteData(0x7e);
    LCD_IO_WriteReg(0xd41e);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd41f);
    LCD_IO_WriteData(0xbc);
    LCD_IO_WriteReg(0xd420);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd421);
    LCD_IO_WriteData(0xe1);
    LCD_IO_WriteReg(0xd422);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd423);
    LCD_IO_WriteData(0x10);
    LCD_IO_WriteReg(0xd424);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd425);
    LCD_IO_WriteData(0x31);
    LCD_IO_WriteReg(0xd426);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd427);
    LCD_IO_WriteData(0x5a);
    LCD_IO_WriteReg(0xd428);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd429);
    LCD_IO_WriteData(0x73);
    LCD_IO_WriteReg(0xd42a);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd42b);
    LCD_IO_WriteData(0x94);
    LCD_IO_WriteReg(0xd42c);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd42d);
    LCD_IO_WriteData(0x9f);
    LCD_IO_WriteReg(0xd42e);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd42f);
    LCD_IO_WriteData(0xb3);
    LCD_IO_WriteReg(0xd430);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd431);
    LCD_IO_WriteData(0xb9);
    LCD_IO_WriteReg(0xd432);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd433);
    LCD_IO_WriteData(0xc1);

    //#g-//////////////////////////////////////////////
    LCD_IO_WriteReg(0xd500);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd501);
    LCD_IO_WriteData(0x37);
    LCD_IO_WriteReg(0xd502);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd503);
    LCD_IO_WriteData(0x52);
    LCD_IO_WriteReg(0xd504);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd505);
    LCD_IO_WriteData(0x7b);
    LCD_IO_WriteReg(0xd506);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd507);
    LCD_IO_WriteData(0x99);
    LCD_IO_WriteReg(0xd508);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd509);
    LCD_IO_WriteData(0xb1);
    LCD_IO_WriteReg(0xd50a);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd50b);
    LCD_IO_WriteData(0xd2);
    LCD_IO_WriteReg(0xd50c);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd50d);
    LCD_IO_WriteData(0xf6);
    LCD_IO_WriteReg(0xd50e);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd50f);
    LCD_IO_WriteData(0x27);
    LCD_IO_WriteReg(0xd510);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd511);
    LCD_IO_WriteData(0x4e);
    LCD_IO_WriteReg(0xd512);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd513);
    LCD_IO_WriteData(0x8c);
    LCD_IO_WriteReg(0xd514);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd515);
    LCD_IO_WriteData(0xbe);
    LCD_IO_WriteReg(0xd516);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd517);
    LCD_IO_WriteData(0x0b);
    LCD_IO_WriteReg(0xd518);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd519);
    LCD_IO_WriteData(0x48);
    LCD_IO_WriteReg(0xd51a);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd51b);
    LCD_IO_WriteData(0x4a);
    LCD_IO_WriteReg(0xd51c);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd51d);
    LCD_IO_WriteData(0x7e);
    LCD_IO_WriteReg(0xd51e);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd51f);
    LCD_IO_WriteData(0xbc);
    LCD_IO_WriteReg(0xd520);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd521);
    LCD_IO_WriteData(0xe1);
    LCD_IO_WriteReg(0xd522);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd523);
    LCD_IO_WriteData(0x10);
    LCD_IO_WriteReg(0xd524);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd525);
    LCD_IO_WriteData(0x31);
    LCD_IO_WriteReg(0xd526);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd527);
    LCD_IO_WriteData(0x5a);
    LCD_IO_WriteReg(0xd528);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd529);
    LCD_IO_WriteData(0x73);
    LCD_IO_WriteReg(0xd52a);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd52b);
    LCD_IO_WriteData(0x94);
    LCD_IO_WriteReg(0xd52c);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd52d);
    LCD_IO_WriteData(0x9f);
    LCD_IO_WriteReg(0xd52e);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd52f);
    LCD_IO_WriteData(0xb3);
    LCD_IO_WriteReg(0xd530);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd531);
    LCD_IO_WriteData(0xb9);
    LCD_IO_WriteReg(0xd532);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd533);
    LCD_IO_WriteData(0xc1);
    //#b-///////////////////////////////
    LCD_IO_WriteReg(0xd600);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd601);
    LCD_IO_WriteData(0x37);
    LCD_IO_WriteReg(0xd602);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd603);
    LCD_IO_WriteData(0x52);
    LCD_IO_WriteReg(0xd604);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd605);
    LCD_IO_WriteData(0x7b);
    LCD_IO_WriteReg(0xd606);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd607);
    LCD_IO_WriteData(0x99);
    LCD_IO_WriteReg(0xd608);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd609);
    LCD_IO_WriteData(0xb1);
    LCD_IO_WriteReg(0xd60a);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd60b);
    LCD_IO_WriteData(0xd2);
    LCD_IO_WriteReg(0xd60c);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xd60d);
    LCD_IO_WriteData(0xf6);
    LCD_IO_WriteReg(0xd60e);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd60f);
    LCD_IO_WriteData(0x27);
    LCD_IO_WriteReg(0xd610);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd611);
    LCD_IO_WriteData(0x4e);
    LCD_IO_WriteReg(0xd612);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd613);
    LCD_IO_WriteData(0x8c);
    LCD_IO_WriteReg(0xd614);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xd615);
    LCD_IO_WriteData(0xbe);
    LCD_IO_WriteReg(0xd616);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd617);
    LCD_IO_WriteData(0x0b);
    LCD_IO_WriteReg(0xd618);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd619);
    LCD_IO_WriteData(0x48);
    LCD_IO_WriteReg(0xd61a);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd61b);
    LCD_IO_WriteData(0x4a);
    LCD_IO_WriteReg(0xd61c);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd61d);
    LCD_IO_WriteData(0x7e);
    LCD_IO_WriteReg(0xd61e);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd61f);
    LCD_IO_WriteData(0xbc);
    LCD_IO_WriteReg(0xd620);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xd621);
    LCD_IO_WriteData(0xe1);
    LCD_IO_WriteReg(0xd622);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd623);
    LCD_IO_WriteData(0x10);
    LCD_IO_WriteReg(0xd624);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd625);
    LCD_IO_WriteData(0x31);
    LCD_IO_WriteReg(0xd626);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd627);
    LCD_IO_WriteData(0x5a);
    LCD_IO_WriteReg(0xd628);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd629);
    LCD_IO_WriteData(0x73);
    LCD_IO_WriteReg(0xd62a);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd62b);
    LCD_IO_WriteData(0x94);
    LCD_IO_WriteReg(0xd62c);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd62d);
    LCD_IO_WriteData(0x9f);
    LCD_IO_WriteReg(0xd62e);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd62f);
    LCD_IO_WriteData(0xb3);
    LCD_IO_WriteReg(0xd630);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd631);
    LCD_IO_WriteData(0xb9);
    LCD_IO_WriteReg(0xd632);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xd633);
    LCD_IO_WriteData(0xc1);



    //#enable page0
    LCD_IO_WriteReg(0xf000);
    LCD_IO_WriteData(0x55);
    LCD_IO_WriteReg(0xf001);
    LCD_IO_WriteData(0xaa);
    LCD_IO_WriteReg(0xf002);
    LCD_IO_WriteData(0x52);
    LCD_IO_WriteReg(0xf003);
    LCD_IO_WriteData(0x08);
    LCD_IO_WriteReg(0xf004);
    LCD_IO_WriteData(0x00);
    //# rgb i/f setting
    LCD_IO_WriteReg(0xb000);
    LCD_IO_WriteData(0x08);
    LCD_IO_WriteReg(0xb001);
    LCD_IO_WriteData(0x05);
    LCD_IO_WriteReg(0xb002);
    LCD_IO_WriteData(0x02);
    LCD_IO_WriteReg(0xb003);
    LCD_IO_WriteData(0x05);
    LCD_IO_WriteReg(0xb004);
    LCD_IO_WriteData(0x02);
    //## sdt:
    LCD_IO_WriteReg(0xb600);
    LCD_IO_WriteData(0x08);
    LCD_IO_WriteReg(0xb500);
    LCD_IO_WriteData(0x50);//0x6b ???? 480x854       0x50 ???? 480x800

    //## gate eq:
    LCD_IO_WriteReg(0xb700);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xb701);
    LCD_IO_WriteData(0x00);

    //## source eq:
    LCD_IO_WriteReg(0xb800);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xb801);
    LCD_IO_WriteData(0x05);
    LCD_IO_WriteReg(0xb802);
    LCD_IO_WriteData(0x05);
    LCD_IO_WriteReg(0xb803);
    LCD_IO_WriteData(0x05);

    //# inversion: column inversion (nvt)
    LCD_IO_WriteReg(0xbc00);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xbc01);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xbc02);
    LCD_IO_WriteData(0x00);

    //# boe's setting(default)
    LCD_IO_WriteReg(0xcc00);
    LCD_IO_WriteData(0x03);
    LCD_IO_WriteReg(0xcc01);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0xcc02);
    LCD_IO_WriteData(0x00);

    //# display timing:
    LCD_IO_WriteReg(0xbd00);
    LCD_IO_WriteData(0x01);
    LCD_IO_WriteReg(0xbd01);
    LCD_IO_WriteData(0x84);
    LCD_IO_WriteReg(0xbd02);
    LCD_IO_WriteData(0x07);
    LCD_IO_WriteReg(0xbd03);
    LCD_IO_WriteData(0x31);
    LCD_IO_WriteReg(0xbd04);
    LCD_IO_WriteData(0x00);

    LCD_IO_WriteReg(0xba00);
    LCD_IO_WriteData(0x01);

    LCD_IO_WriteReg(0xff00);
    LCD_IO_WriteData(0xaa);
    LCD_IO_WriteReg(0xff01);
    LCD_IO_WriteData(0x55);
    LCD_IO_WriteReg(0xff02);
    LCD_IO_WriteData(0x25);
    LCD_IO_WriteReg(0xff03);
    LCD_IO_WriteData(0x01);

    LCD_IO_WriteReg(0x3500);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0x3600);
    LCD_IO_WriteData(0x00);
    LCD_IO_WriteReg(0x3a00);
    LCD_IO_WriteData(0x55); 
    LCD_IO_WriteReg(0x1100);
    HAL_Delay(120);
    LCD_IO_WriteReg(0x2900 );
    LCD_IO_WriteReg(0x2c00);

    LCD_IO_Write(0x3600, 0x00);
}

void LCD_IO_SetWindow(
    const uint16_t xStartPosition,
    const uint16_t xEndPosition,
    const uint16_t yStartPosition,
    const uint16_t yEndPosition
) {
    LCD_IO_WriteReg(0x2a00 + 0);
    LCD_IO_WriteData(
        xStartPosition >> 8
    );

    LCD_IO_WriteReg(0x2a00 + 1);
    LCD_IO_WriteData(
        xStartPosition & 0xff
    );

    LCD_IO_WriteReg(0x2a00 + 2);
    LCD_IO_WriteData(
        xEndPosition >> 8
    );

    LCD_IO_WriteReg(0x2a00 + 3);
    LCD_IO_WriteData(
        xEndPosition & 0xff
    );

    LCD_IO_WriteReg(0x2b00 + 0);
    LCD_IO_WriteData(
        yStartPosition >> 8
    );

    LCD_IO_WriteReg(0x2b00 + 1);
    LCD_IO_WriteData(
        yStartPosition & 0xff
    );

    LCD_IO_WriteReg(0x2b00 + 2);
    LCD_IO_WriteData(
        yEndPosition >> 8
    );

    LCD_IO_WriteReg(0x2b00 + 3);
    LCD_IO_WriteData(
        yEndPosition & 0xff
    );
}

void LCD_DrawRectangle(
    const uint16_t rgbColor,
    const uint16_t xStartPosition,
    const uint16_t xEndPosition,
    const uint16_t yStartPosition,
    const uint16_t yEndPosition
) {
	LCD_IO_SetWindow(
        xStartPosition,
        yStartPosition,
        xEndPosition,
        yEndPosition
    );

    LCD_IO_WriteReg(0x2c00);

    const uint16_t height = yEndPosition - yStartPosition;
    const uint16_t width = xEndPosition - xStartPosition;

	for(uint16_t y = 0; y < height; y++) {
		for(uint16_t x = 0; x < width; x++) {
            LCD_IO_WriteData(rgbColor);
        }
	}
	
    LCD_IO_SetWindow(0, 0, 480 - 1, 800 - 1);
}

void ATC_Init() {
    LCD_IO_Init();
    LCD_DrawRectangle(
        0x00ff,
        0,
        0,
        250,
        250
    );
}

void ATC_Loop() {

}