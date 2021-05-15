#ifndef ColorPalette_H
#define ColorPalette_H

#include <QString>
#include <QColor>

#include <vector>
#include <map>
#include <cassert>

#define ColorPaletteInst ColorPalette::instance()

class ColorPalette {
 public:
  struct ColorData {
    QString id;
    QColor  color;
    bool    accent { false };

    ColorData(const QString &id1=QString(), const QColor &color1=QColor(), bool accent1=false) :
     id(id1), color(color1), accent(accent1) {
    }
  };

  //---

  class ColorSet {
   public:
    ColorSet(const QString &name) :
     name_(name) {
    }

    void getColorIds(std::vector<QString> &ids) const {
      for (Colors::const_iterator p = colors_.begin(); p != colors_.end(); ++p)
        ids.push_back((*p).first);
    }

    const QColor &getColor(const QString &id) const {
      Colors::const_iterator p = colors_.find(id);
      assert(p != colors_.end());

      return (*p).second.color;
    }

    void addColor(const QString &colorId, const QString &colorName, bool accent=false) {
      colors_[colorId] = ColorData(colorId, QColor(colorName), accent);
    }

    bool isAccent(const QString &id) const {
      Colors::const_iterator p = colors_.find(id);
      assert(p != colors_.end());

      return (*p).second.accent;
    }

   private:
    typedef std::map<QString,ColorData> Colors;

    QString name_;
    Colors  colors_;
  };

  //---

 public:
  static ColorPalette *instance();

  static QColor textColor(const QColor &c);

  bool hasColorSet(const QString &name) const;

  const ColorPalette::ColorSet &getColorSet(const QString &name) const;

  const QColor &getColor(const QString &name, const QString &id) const;

  uint numColorSets() const { return colorSets_.size(); }

  void getColorSetNames(std::vector<QString> &names) const;

  QColor getColorSetBase(const QString &name) const;

 private:
  ColorPalette();
 ~ColorPalette();

  void init();

  ColorPalette::ColorSet &createColorSet(const QString &name);

  void addColor(ColorSet &colorSet, const QString &colorId, const QString &colorName);

 private:
  typedef std::map<QString,ColorSet> ColorSets;
  typedef std::vector<QString>       ColorSetNames;

  QString       name_;
  ColorSets     colorSets_;
  ColorSetNames colorSetNames_;
};

#endif
