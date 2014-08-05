#include <CColorPalette.h>

ColorPalette *
ColorPalette::
instance()
{
  static ColorPalette *instance;

  if (! instance)
    instance = new ColorPalette;

  return instance;
}

QColor
ColorPalette::
textColor(const QColor &c)
{
  int gray = qGray(c.red(), c.green(), c.blue());

  return (gray <= 127 ? QColor(255,255,255) : QColor(0,0,0));
}

ColorPalette::
ColorPalette()
{
  init();
}

ColorPalette::ColorSet &
ColorPalette::
createColorSet(const QString &name)
{
  ColorSets::iterator p = colorSets_.find(name);

  if (p == colorSets_.end()) {
    p = colorSets_.insert(p, ColorSets::value_type(name, ColorSet(name)));

    colorSetNames_.push_back(name);
  }

  return (*p).second;
}

const ColorPalette::ColorSet &
ColorPalette::
getColorSet(const QString &name) const
{
  ColorSets::const_iterator p = colorSets_.find(name);
  assert(p != colorSets_.end());

  return (*p).second;
}

const QColor &
ColorPalette::
getColor(const QString &name, const QString &id) const
{
  return getColorSet(name).getColor(id);
}

void
ColorPalette::
getColorSetNames(std::vector<QString> &names) const
{
  for (ColorSetNames::const_iterator p = colorSetNames_.begin(); p != colorSetNames_.end(); ++p)
    names.push_back(*p);
}

QColor
ColorPalette::
getColorSetBase(const QString &name) const
{
  return getColorSet(name).getColor("500");
}

void
ColorPalette::
addColor(ColorSet &colorSet, const QString &colorId, const QString &colorName)
{
  bool accent = (colorId.at(0) == 'A');

  colorSet.addColor(colorId, colorName, accent);
}

void
ColorPalette::
init()
{
  ColorSet &redSet = createColorSet("Red");

  addColor(redSet, "050" , "#fde0dc");
  addColor(redSet, "100" , "#f9bdbb");
  addColor(redSet, "200" , "#f69988");
  addColor(redSet, "300" , "#f36c60");
  addColor(redSet, "400" , "#e84e40");
  addColor(redSet, "500" , "#e51c23");
  addColor(redSet, "600" , "#dd191d");
  addColor(redSet, "700" , "#d01716");
  addColor(redSet, "800" , "#c41411");
  addColor(redSet, "900" , "#b0120a");
  addColor(redSet, "A100", "#ff7997");
  addColor(redSet, "A200", "#ff5177");
  addColor(redSet, "A400", "#ff2d6f");
  addColor(redSet, "A700", "#e00032");

  ColorSet &pinkSet = createColorSet("Pink");

  addColor(pinkSet, "050" , "#fce4ec");
  addColor(pinkSet, "100" , "#f8bbd0");
  addColor(pinkSet, "200" , "#f48fb1");
  addColor(pinkSet, "300" , "#f06292");
  addColor(pinkSet, "400" , "#ec407a");
  addColor(pinkSet, "500" , "#e91e63");
  addColor(pinkSet, "600" , "#d81b60");
  addColor(pinkSet, "700" , "#c2185b");
  addColor(pinkSet, "800" , "#ad1457");
  addColor(pinkSet, "900" , "#880e4f");
  addColor(pinkSet, "A100", "#ff80ab");
  addColor(pinkSet, "A200", "#ff4081");
  addColor(pinkSet, "A400", "#f50057");
  addColor(pinkSet, "A700", "#c51162");

  ColorSet &purpleSet = createColorSet("Purple");

  addColor(purpleSet, "050" , "#f3e5f5");
  addColor(purpleSet, "100" , "#e1bee7");
  addColor(purpleSet, "200" , "#ce93d8");
  addColor(purpleSet, "300" , "#ba68c8");
  addColor(purpleSet, "400" , "#ab47bc");
  addColor(purpleSet, "500" , "#9c27b0");
  addColor(purpleSet, "600" , "#8e24aa");
  addColor(purpleSet, "700" , "#7b1fa2");
  addColor(purpleSet, "800" , "#6a1b9a");
  addColor(purpleSet, "900" , "#4a148c");
  addColor(purpleSet, "A100", "#ea80fc");
  addColor(purpleSet, "A200", "#e040fb");
  addColor(purpleSet, "A400", "#d500f9");
  addColor(purpleSet, "A700", "#aa00ff");

  ColorSet &deepPurpleSet = createColorSet("Deep Purple");

  addColor(deepPurpleSet, "050" , "#ede7f6");
  addColor(deepPurpleSet, "100" , "#d1c4e9");
  addColor(deepPurpleSet, "200" , "#b39ddb");
  addColor(deepPurpleSet, "300" , "#9575cd");
  addColor(deepPurpleSet, "400" , "#7e57c2");
  addColor(deepPurpleSet, "500" , "#673ab7");
  addColor(deepPurpleSet, "600" , "#5e35b1");
  addColor(deepPurpleSet, "700" , "#512da8");
  addColor(deepPurpleSet, "800" , "#4527a0");
  addColor(deepPurpleSet, "900" , "#311b92");
  addColor(deepPurpleSet, "A100", "#b388ff");
  addColor(deepPurpleSet, "A200", "#7c4dff");
  addColor(deepPurpleSet, "A400", "#651fff");
  addColor(deepPurpleSet, "A700", "#6200ea");

  ColorSet &indigoSet = createColorSet("Indigo");

  addColor(indigoSet, "050" , "#e8eaf6");
  addColor(indigoSet, "100" , "#c5cae9");
  addColor(indigoSet, "200" , "#9fa8da");
  addColor(indigoSet, "300" , "#7986cb");
  addColor(indigoSet, "400" , "#5c6bc0");
  addColor(indigoSet, "500" , "#3f51b5");
  addColor(indigoSet, "600" , "#3949ab");
  addColor(indigoSet, "700" , "#303f9f");
  addColor(indigoSet, "800" , "#283593");
  addColor(indigoSet, "900" , "#1a237e");
  addColor(indigoSet, "A100", "#8c9eff");
  addColor(indigoSet, "A200", "#536dfe");
  addColor(indigoSet, "A400", "#3d5afe");
  addColor(indigoSet, "A700", "#304ffe");

  ColorSet &blueSet = createColorSet("Blue");

  addColor(blueSet, "050" , "#e7e9fd");
  addColor(blueSet, "100" , "#d0d9ff");
  addColor(blueSet, "200" , "#afbfff");
  addColor(blueSet, "300" , "#91a7ff");
  addColor(blueSet, "400" , "#738ffe");
  addColor(blueSet, "500" , "#5677fc");
  addColor(blueSet, "600" , "#4e6cef");
  addColor(blueSet, "700" , "#455ede");
  addColor(blueSet, "800" , "#3b50ce");
  addColor(blueSet, "900" , "#2a36b1");
  addColor(blueSet, "A100", "#a6baff");
  addColor(blueSet, "A200", "#6889ff");
  addColor(blueSet, "A400", "#4d73ff");
  addColor(blueSet, "A700", "#4d69ff");

  ColorSet &lightBlueSet = createColorSet("Light Blue");

  addColor(lightBlueSet, "050" , "#e1f5fe");
  addColor(lightBlueSet, "100" , "#b3e5fc");
  addColor(lightBlueSet, "200" , "#81d4fa");
  addColor(lightBlueSet, "300" , "#4fc3f7");
  addColor(lightBlueSet, "400" , "#29b6f6");
  addColor(lightBlueSet, "500" , "#03a9f4");
  addColor(lightBlueSet, "600" , "#039be5");
  addColor(lightBlueSet, "700" , "#0288d1");
  addColor(lightBlueSet, "800" , "#0277bd");
  addColor(lightBlueSet, "900" , "#01579b");
  addColor(lightBlueSet, "A100", "#80d8ff");
  addColor(lightBlueSet, "A200", "#40c4ff");
  addColor(lightBlueSet, "A400", "#00b0ff");
  addColor(lightBlueSet, "A700", "#0091ea");

  ColorSet &cyanSet = createColorSet("Cyan");

  addColor(cyanSet, "050" , "#e0f7fa");
  addColor(cyanSet, "100" , "#b2ebf2");
  addColor(cyanSet, "200" , "#80deea");
  addColor(cyanSet, "300" , "#4dd0e1");
  addColor(cyanSet, "400" , "#26c6da");
  addColor(cyanSet, "500" , "#00bcd4");
  addColor(cyanSet, "600" , "#00acc1");
  addColor(cyanSet, "700" , "#0097a7");
  addColor(cyanSet, "800" , "#00838f");
  addColor(cyanSet, "900" , "#006064");
  addColor(cyanSet, "A100", "#84ffff");
  addColor(cyanSet, "A200", "#18ffff");
  addColor(cyanSet, "A400", "#00e5ff");
  addColor(cyanSet, "A700", "#00b8d4");

  ColorSet &tealSet = createColorSet("Teal");

  addColor(tealSet, "050" , "#e0f2f1");
  addColor(tealSet, "100" , "#b2dfdb");
  addColor(tealSet, "200" , "#80cbc4");
  addColor(tealSet, "300" , "#4db6ac");
  addColor(tealSet, "400" , "#26a69a");
  addColor(tealSet, "500" , "#009688");
  addColor(tealSet, "600" , "#00897b");
  addColor(tealSet, "700" , "#00796b");
  addColor(tealSet, "800" , "#00695c");
  addColor(tealSet, "900" , "#004d40");
  addColor(tealSet, "A100", "#a7ffeb");
  addColor(tealSet, "A200", "#64ffda");
  addColor(tealSet, "A400", "#1de9b6");
  addColor(tealSet, "A700", "#00bfa5");

  ColorSet &greenSet = createColorSet("Green");

  addColor(greenSet, "050" , "#d0f8ce");
  addColor(greenSet, "100" , "#a3e9a4");
  addColor(greenSet, "200" , "#72d572");
  addColor(greenSet, "300" , "#42bd41");
  addColor(greenSet, "400" , "#2baf2b");
  addColor(greenSet, "500" , "#259b24");
  addColor(greenSet, "600" , "#0a8f08");
  addColor(greenSet, "700" , "#0a7e07");
  addColor(greenSet, "800" , "#056f00");
  addColor(greenSet, "900" , "#0d5302");
  addColor(greenSet, "A100", "#a2f78d");
  addColor(greenSet, "A200", "#5af158");
  addColor(greenSet, "A400", "#14e715");
  addColor(greenSet, "A700", "#12c700");

  ColorSet &lightGreenSet = createColorSet("Light Green");

  addColor(lightGreenSet, "050" , "#f1f8e9");
  addColor(lightGreenSet, "100" , "#dcedc8");
  addColor(lightGreenSet, "200" , "#c5e1a5");
  addColor(lightGreenSet, "300" , "#aed581");
  addColor(lightGreenSet, "400" , "#9ccc65");
  addColor(lightGreenSet, "500" , "#8bc34a");
  addColor(lightGreenSet, "600" , "#7cb342");
  addColor(lightGreenSet, "700" , "#689f38");
  addColor(lightGreenSet, "800" , "#558b2f");
  addColor(lightGreenSet, "900" , "#33691e");
  addColor(lightGreenSet, "A100", "#ccff90");
  addColor(lightGreenSet, "A200", "#b2ff59");
  addColor(lightGreenSet, "A400", "#76ff03");
  addColor(lightGreenSet, "A700", "#64dd17");

  ColorSet &limeSet = createColorSet("Lime");

  addColor(limeSet, "050" , "#f9fbe7");
  addColor(limeSet, "100" , "#f0f4c3");
  addColor(limeSet, "200" , "#e6ee9c");
  addColor(limeSet, "300" , "#dce775");
  addColor(limeSet, "400" , "#d4e157");
  addColor(limeSet, "500" , "#cddc39");
  addColor(limeSet, "600" , "#c0ca33");
  addColor(limeSet, "700" , "#afb42b");
  addColor(limeSet, "800" , "#9e9d24");
  addColor(limeSet, "900" , "#827717");
  addColor(limeSet, "A100", "#f4ff81");
  addColor(limeSet, "A200", "#eeff41");
  addColor(limeSet, "A400", "#c6ff00");
  addColor(limeSet, "A700", "#aeea00");

  ColorSet &yellowSet = createColorSet("Yellow");

  addColor(yellowSet, "050" , "#fffde7");
  addColor(yellowSet, "100" , "#fff9c4");
  addColor(yellowSet, "200" , "#fff59d");
  addColor(yellowSet, "300" , "#fff176");
  addColor(yellowSet, "400" , "#ffee58");
  addColor(yellowSet, "500" , "#ffeb3b");
  addColor(yellowSet, "600" , "#fdd835");
  addColor(yellowSet, "700" , "#fbc02d");
  addColor(yellowSet, "800" , "#f9a825");
  addColor(yellowSet, "900" , "#f57f17");
  addColor(yellowSet, "A100", "#ffff8d");
  addColor(yellowSet, "A200", "#ffff00");
  addColor(yellowSet, "A400", "#ffea00");
  addColor(yellowSet, "A700", "#ffd600");

  ColorSet &amberSet = createColorSet("Amber");

  addColor(amberSet, "050" , "#fff8e1");
  addColor(amberSet, "100" , "#ffecb3");
  addColor(amberSet, "200" , "#ffe082");
  addColor(amberSet, "300" , "#ffd54f");
  addColor(amberSet, "400" , "#ffca28");
  addColor(amberSet, "500" , "#ffc107");
  addColor(amberSet, "600" , "#ffb300");
  addColor(amberSet, "700" , "#ffa000");
  addColor(amberSet, "800" , "#ff8f00");
  addColor(amberSet, "900" , "#ff6f00");
  addColor(amberSet, "A100", "#ffe57f");
  addColor(amberSet, "A200", "#ffd740");
  addColor(amberSet, "A400", "#ffc400");
  addColor(amberSet, "A700", "#ffab00");

  ColorSet &orangeSet = createColorSet("Orange");

  addColor(orangeSet, "050" , "#fff3e0");
  addColor(orangeSet, "100" , "#ffe0b2");
  addColor(orangeSet, "200" , "#ffcc80");
  addColor(orangeSet, "300" , "#ffb74d");
  addColor(orangeSet, "400" , "#ffa726");
  addColor(orangeSet, "500" , "#ff9800");
  addColor(orangeSet, "600" , "#fb8c00");
  addColor(orangeSet, "700" , "#f57c00");
  addColor(orangeSet, "800" , "#ef6c00");
  addColor(orangeSet, "900" , "#e65100");
  addColor(orangeSet, "A100", "#ffd180");
  addColor(orangeSet, "A200", "#ffab40");
  addColor(orangeSet, "A400", "#ff9100");
  addColor(orangeSet, "A700", "#ff6d00");

  ColorSet &deepOrangeSet = createColorSet("Deep Orange");

  addColor(deepOrangeSet, "050" , "#fbe9e7");
  addColor(deepOrangeSet, "100" , "#ffccbc");
  addColor(deepOrangeSet, "200" , "#ffab91");
  addColor(deepOrangeSet, "300" , "#ff8a65");
  addColor(deepOrangeSet, "400" , "#ff7043");
  addColor(deepOrangeSet, "500" , "#ff5722");
  addColor(deepOrangeSet, "600" , "#f4511e");
  addColor(deepOrangeSet, "700" , "#e64a19");
  addColor(deepOrangeSet, "800" , "#d84315");
  addColor(deepOrangeSet, "900" , "#bf360c");
  addColor(deepOrangeSet, "A100", "#ff9e80");
  addColor(deepOrangeSet, "A200", "#ff6e40");
  addColor(deepOrangeSet, "A400", "#ff3d00");
  addColor(deepOrangeSet, "A700", "#dd2c00");

  ColorSet &brownSet = createColorSet("Brown");

  addColor(brownSet, "050" , "#efebe9");
  addColor(brownSet, "100" , "#d7ccc8");
  addColor(brownSet, "200" , "#bcaaa4");
  addColor(brownSet, "300" , "#a1887f");
  addColor(brownSet, "400" , "#8d6e63");
  addColor(brownSet, "500" , "#795548");
  addColor(brownSet, "600" , "#6d4c41");
  addColor(brownSet, "700" , "#5d4037");
  addColor(brownSet, "800" , "#4e342e");
  addColor(brownSet, "900" , "#3e2723");

  ColorSet &greySet = createColorSet("Grey");

  addColor(greySet, "000", "#ffffff");
  addColor(greySet, "050", "#fafafa");
  addColor(greySet, "100", "#f5f5f5");
  addColor(greySet, "200", "#eeeeee");
  addColor(greySet, "300", "#e0e0e0");
  addColor(greySet, "400", "#bdbdbd");
  addColor(greySet, "500", "#9e9e9e");
  addColor(greySet, "600", "#757575");
  addColor(greySet, "700", "#616161");
  addColor(greySet, "800", "#424242");
  addColor(greySet, "900", "#212121");
  addColor(greySet, "999", "#000000");

  ColorSet &blueGreySet = createColorSet("Blue Grey");

  addColor(blueGreySet, "050", "#eceff1");
  addColor(blueGreySet, "100", "#cfd8dc");
  addColor(blueGreySet, "200", "#b0bec5");
  addColor(blueGreySet, "300", "#90a4ae");
  addColor(blueGreySet, "400", "#78909c");
  addColor(blueGreySet, "500", "#607d8b");
  addColor(blueGreySet, "600", "#546e7a");
  addColor(blueGreySet, "700", "#455a64");
  addColor(blueGreySet, "800", "#37474f");
  addColor(blueGreySet, "900", "#263238");
}
