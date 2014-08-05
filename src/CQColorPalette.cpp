#include <CQColorPalette.h>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QItemDelegate>
#include <QPainter>

CQColorPalette::
CQColorPalette() :
 QFrame(), style_(ColorStyle), colorSet_("Red"), colorId_("500")
{
  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->setMargin(2); layout->setSpacing(2);

  QHBoxLayout *hlayout = new QHBoxLayout;
  hlayout->setMargin(2); hlayout->setSpacing(8);

  //----

  colorTable_ = new CQColorTable(this);

  connect(colorTable_, SIGNAL(colorSelected(const QString &)),
          this, SLOT(colorSelected(const QString &)));

  hlayout->addWidget(colorTable_);

  colorTable_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  //----

  colorList_ = new CQColorList(this);

  connect(colorList_, SIGNAL(colorSelected(const QString &)),
          this, SLOT(colorSelected(const QString &)));

  hlayout->addWidget(colorList_);

  //----

  itemList_ = new CQColorItemList(this);

  connect(itemList_, SIGNAL(colorItemSelected(const QString &)),
          this, SLOT(colorItemSelected(const QString &)));

  hlayout->addWidget(itemList_);

  //----

  layout->addLayout(hlayout);

  //----

  QHBoxLayout *slayout = new QHBoxLayout;
  slayout->setMargin(2); slayout->setSpacing(2);

  slayout->addWidget(new QLabel("Fg:"));

  fgStatusLabel_ = new CQColorLabel(CQColorLabel::FgType);

  slayout->addWidget(fgStatusLabel_);

  slayout->addWidget(new QLabel("Bg:"));

  bgStatusLabel_ = new CQColorLabel(CQColorLabel::BgType);

  slayout->addWidget(bgStatusLabel_);

  slayout->addStretch(1);

  layout->addLayout(slayout);

  connect(this, SIGNAL(colorChanged(const QString &, const QString &, const QColor &)),
          fgStatusLabel_, SLOT(colorChanged(const QString &, const QString &, const QColor &)));
  connect(this, SIGNAL(colorChanged(const QString &, const QString &, const QColor &)),
          bgStatusLabel_, SLOT(colorChanged(const QString &, const QString &, const QColor &)));

  //----

  colorTable_->setVisible(style_ == SetStyle);
  colorList_ ->setVisible(style_ == ColorStyle);
  itemList_  ->setVisible(style_ == ColorStyle);

  colorItemSelected("500");

  setMinimumWidth(500);
}

void
CQColorPalette::
setStyle(const Style &style)
{
  style_ = style;

  colorTable_->setVisible(style_ == SetStyle);
  colorList_ ->setVisible(style_ == ColorStyle);
  itemList_  ->setVisible(style_ == ColorStyle);

  updateList();
}

void
CQColorPalette::
setColorSet(const QString &name)
{
  colorSet_ = name;

  setColorId("500");
}

void
CQColorPalette::
setColorId(const QString &name)
{
  colorId_ = name;

  updateList();

  emitColorChanged();
}

void
CQColorPalette::
colorSelected(const QString &name)
{
  setColorSet(name);
}

void
CQColorPalette::
colorItemSelected(const QString &name)
{
  setColorId(name);
}

void
CQColorPalette::
emitColorChanged()
{
  const ColorPalette::ColorSet &colorSet = ColorPaletteInst->getColorSet(colorSet_);

  QColor color = colorSet.getColor(colorId_);

  emit colorChanged(colorSet_, colorId_, color);
}

void
CQColorPalette::
updateList()
{
  const QColor &color = ColorPaletteInst->getColorSetBase(colorSet_);

  if (style_ == ColorStyle) {
    const ColorPalette::ColorSet &colorSet = ColorPaletteInst->getColorSet(colorSet_);

    std::vector<QString> ids;

    colorSet.getColorIds(ids);

    //---

    itemList_->blockSignals(true);

    itemList_->clear();

    itemList_->addColorTitle(colorSet_, color);

    itemList_->addSeparator();

    itemList_->addTitle("Primary");

    bool is_a = false;

    int row = 0;

    for (uint i = 0; i < ids.size(); ++i) {
      const QString &id = ids[i];

      if (id == "500")
        row = i;

      if (! is_a && colorSet.isAccent(id)) {
        itemList_->addSeparator();

        itemList_->addTitle("Accent");

        is_a = true;
      }

      const QColor &color1 = colorSet.getColor(id);

      itemList_->addItem(id, color1);
    }

    itemList_->setCurrentRow(row + 3);

    itemList_->blockSignals(false);
  }

  colorList_ ->setColorSet(colorSet_);
  colorTable_->setColorSet(colorSet_);

  //----

  emit colorChanged(colorSet_, colorId_, color);
}

//------

class CQColorTableItem : public QTableWidgetItem {
 public:
  CQColorTableItem(CQColorTable *table, const QString &name, const QColor &color) :
   table_(table), name_(name), color_(color) {
  }

  const QString &name () const { return name_ ; }
  const QColor  &color() const { return color_; }

 private:
  CQColorTable *table_;
  QString       name_;
  QColor        color_;
};

class CQColorTableDelegate : public QItemDelegate {
 public:
  CQColorTableDelegate(CQColorTable *table) :
   table_(table) {
  }

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const {
    CQColorTableItem *item =
      static_cast<CQColorTableItem *>(table_->item(index.row(), index.column()));
    if (! item) return;

    painter->fillRect(option.rect, item->color());

    QFontMetrics fm(table_->font());

    int border = 4;

    int t = option.rect.top   () + border;
    int l = option.rect.left  () + border;
    int b = option.rect.bottom() - border;

    int h = fm.height()         + 2*border;
    int w = option.rect.width() - 2*border;

    painter->setPen(ColorPalette::textColor(item->color()));

    QRect r1(l, t, w, h);

    painter->drawText(r1.left(), r1.top(), r1.width(), r1.height(),
                      Qt::AlignLeft | Qt::AlignVCenter,
                      item->name());

    QRect r2(l, b - h, w, h);

    painter->drawText(r2.left(), r2.top(), r2.width(), r2.height(),
                      Qt::AlignLeft | Qt::AlignVCenter,
                      "500");

    painter->drawText(r2.left(), r2.top(), r2.width(), r2.height(),
                      Qt::AlignRight | Qt::AlignVCenter,
                      item->color().name());

    if (option.state & QStyle::State_Selected)
      painter->drawRect(option.rect.adjusted(0,0,-1,-1));
  }

  QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const {
    return table_->cellSize();
  }

 private:
  CQColorTable *table_;
};

//------

CQColorTable::
CQColorTable(CQColorPalette *pal) :
 QTableWidget(), pal_(pal), nrows_(0), ncols_(0)
{
  setShowGrid(false);

  horizontalHeader()->hide();
  verticalHeader  ()->hide();

  horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  verticalHeader  ()->setSectionResizeMode(QHeaderView::ResizeToContents);

  setItemDelegate(new CQColorTableDelegate(this));

  connect(this, SIGNAL(currentItemChanged(QTableWidgetItem *, QTableWidgetItem *)),
          this, SLOT(itemSlot(QTableWidgetItem *, QTableWidgetItem *)));

  resizeEvent(0);
}

void
CQColorTable::
setColorSet(const QString &name)
{
  std::vector<QString> names;

  ColorPaletteInst->getColorSetNames(names);

  for (uint i = 0; i < ColorPaletteInst->numColorSets(); ++i) {
    int r = i / ncols_;
    int c = i % ncols_;

    if (names[i] == name)
      setCurrentCell(r, c);
  }
}

void
CQColorTable::
addItems()
{
  clear();

  std::vector<QString> names;

  ColorPaletteInst->getColorSetNames(names);

  for (uint i = 0; i < ColorPaletteInst->numColorSets(); ++i) {
    int r = i / ncols_;
    int c = i % ncols_;

    const QColor &color = ColorPaletteInst->getColorSetBase(names[i]);

    addItem(r, c, names[i], color);

    if (names[i] == pal_->colorSet())
      setCurrentCell(r, c);
  }
}

void
CQColorTable::
addItem(int row, int col, const QString &name, const QColor &color)
{
  QTableWidget::setItem(row, col, new CQColorTableItem(this, name, color));
}

void
CQColorTable::
itemSlot(QTableWidgetItem *item, QTableWidgetItem *)
{
  CQColorTableItem *citem = static_cast<CQColorTableItem *>(item);

  if (citem)
    emit colorSelected(citem->name());
}

void
CQColorTable::
resizeEvent(QResizeEvent *)
{
  int w = width() - 16;

  int ncols = std::max(w/cellSizeHint().width(), 1);

  ncols_ = ncols;
  nrows_ = (ColorPaletteInst->numColorSets() + ncols_ - 1)/ncols_;

  setColumnCount(ncols_);
  setRowCount   (nrows_);

  addItems();
}

QSize
CQColorTable::
cellSizeHint() const
{
  QFontMetrics fm(font());

  //int w = fm.width(item->name());
  int w = fm.width("500#888888");

  return QSize(w + 64, 4*fm.height() + 8);
}

QSize
CQColorTable::
cellSize() const
{
  int w = width() - 16;

  return QSize(w/ncols_, cellSizeHint().height());
}

//------

class CQColorListItem : public QListWidgetItem {
 public:
  CQColorListItem(CQColorList *list, const QString &name, const QColor &color) :
   list_(list), name_(name), color_(color) {
  }

  const QString &name () const { return name_ ; }
  const QColor  &color() const { return color_; }

 private:
  CQColorList *list_;
  QString      name_;
  QColor       color_;
};

class CQColorListDelegate : public QItemDelegate {
 public:
  CQColorListDelegate(CQColorList *list) :
   list_(list) {
  }

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const {
    CQColorListItem *item = static_cast<CQColorListItem *>(list_->item(index.row()));

    painter->fillRect(option.rect, item->color());

    painter->setPen(ColorPalette::textColor(item->color()));

    int border = 4;

    QRect r = option.rect.adjusted(border, 0, -border, 0);

    painter->drawText(r.left(), r.top(), r.width(), r.height(),
                      Qt::AlignLeft | Qt::AlignVCenter,
                      item->name());

    if (option.state & QStyle::State_Selected)
      painter->drawRect(option.rect.adjusted(0,0,-1,-1));
  }

  QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &index) const {
    CQColorListItem *item = static_cast<CQColorListItem *>(list_->item(index.row()));

    QFontMetrics fm(list_->font());

    return QSize(fm.width(item->name()) + 8, fm.height() + 8);
  }

 private:
  CQColorList *list_;
};

//------

CQColorList::
CQColorList(CQColorPalette *pal) :
 QListWidget(), pal_(pal)
{
  setItemDelegate(new CQColorListDelegate(this));

  connect(this, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
          this, SLOT(itemSlot(QListWidgetItem *, QListWidgetItem *)));

  addItems();
}

void
CQColorList::
setColorSet(const QString &name)
{
  std::vector<QString> names;

  ColorPaletteInst->getColorSetNames(names);

  for (uint i = 0; i < ColorPaletteInst->numColorSets(); ++i) {
    if (names[i] == name)
      setCurrentRow(i);
  }
}

void
CQColorList::
addItems()
{
  QFontMetrics fm(font());

  int w = 0;

  clear();

  std::vector<QString> names;

  ColorPaletteInst->getColorSetNames(names);

  for (uint i = 0; i < ColorPaletteInst->numColorSets(); ++i) {
    const QColor &color = ColorPaletteInst->getColorSetBase(names[i]);

    addItem(names[i], color);

    if (names[i] == pal_->colorSet())
      setCurrentRow(i);

    w = std::max(w, fm.width(names[i]));
  }

  setFixedWidth(w + 64);
}

void
CQColorList::
addItem(const QString &name, const QColor &color)
{
  QListWidget::addItem(new CQColorListItem(this, name, color));
}

void
CQColorList::
itemSlot(QListWidgetItem *item, QListWidgetItem *)
{
  CQColorListItem *citem = static_cast<CQColorListItem *>(item);

  if (citem)
    emit colorSelected(citem->name());
}

//------

class CQColorItemListItem : public QListWidgetItem {
 public:
  enum Type {
    Normal,
    ColorTitle,
    Title,
    Separator
  };

 public:
  CQColorItemListItem(CQColorItemList *list, Type type, const QString &name=QString(),
                      const QColor &color=QColor()) :
   list_(list), type_(type), name_(name), color_(color) {
    setSelectable(type == Normal);
  }

  Type type() const { return type_; }

  const QString &name () const { return name_ ; }
  const QColor  &color() const { return color_; }

  void setSelectable(bool selectable) {
    if (selectable)
      setFlags(flags() |  (Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
    else
      setFlags(flags() & ~(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
  }

  bool isSelectable() const {
    return (flags() & (Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled));
  }

 private:
  CQColorItemList *list_;
  Type             type_;
  QString          name_;
  QColor           color_;
};

class CQColorItemListDelegate : public QItemDelegate {
 public:
  CQColorItemListDelegate(CQColorItemList *list) :
   list_(list) {
  }

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const {
    CQColorItemListItem *item = static_cast<CQColorItemListItem *>(list_->item(index.row()));

    if (item->type() == CQColorItemListItem::Separator) {
      painter->fillRect(option.rect, QColor(255,255,255));
      return;
    }

    if (item->color().isValid()) {
      painter->fillRect(option.rect, item->color());

      painter->setPen(ColorPalette::textColor(item->color()));
    }
    else
      painter->setPen(QColor(0,0,0));

    int border = 4;

    QRect r = option.rect.adjusted(border, 0, -border, 0);

    painter->drawText(r.left(), r.top(), r.width(), r.height(),
                      Qt::AlignLeft | Qt::AlignVCenter,
                      item->name());

    if (item->type() != CQColorItemListItem::Title)
      painter->drawText(r.left(), r.top(), r.width(), r.height(),
                        Qt::AlignRight | Qt::AlignVCenter,
                        item->color().name());

    if (option.state & QStyle::State_Selected)
      painter->drawRect(option.rect.adjusted(0,0,-1,-1));
  }

  QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &index) const {
    CQColorItemListItem *item = static_cast<CQColorItemListItem *>(list_->item(index.row()));

    QFontMetrics fm(list_->font());

    if (item->type() == CQColorItemListItem::Separator)
      return QSize(8, 8);
    else
      return QSize(fm.width(item->name()) + 8, fm.height() + 8);
  }

 private:
  CQColorItemList *list_;
};

//------

CQColorItemList::
CQColorItemList(CQColorPalette *pal) :
 QListWidget(), pal_(pal)
{
  setItemDelegate(new CQColorItemListDelegate(this));

  connect(this, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
          this, SLOT(itemSlot(QListWidgetItem *, QListWidgetItem *)));
}

void
CQColorItemList::
addColorTitle(const QString &name, const QColor &color)
{
  QListWidget::addItem(new CQColorItemListItem(this, CQColorItemListItem::ColorTitle, name, color));
}

void
CQColorItemList::
addTitle(const QString &name)
{
  QListWidget::addItem(new CQColorItemListItem(this, CQColorItemListItem::Title, name));
}

void
CQColorItemList::
addSeparator()
{
  QListWidget::addItem(new CQColorItemListItem(this, CQColorItemListItem::Separator));
}

void
CQColorItemList::
addItem(const QString &name, const QColor &color)
{
  QListWidget::addItem(new CQColorItemListItem(this, CQColorItemListItem::Normal, name, color));
}

void
CQColorItemList::
itemSlot(QListWidgetItem *item, QListWidgetItem *)
{
  CQColorItemListItem *citem = static_cast<CQColorItemListItem *>(item);

  if (citem)
    emit colorItemSelected(citem->name());
}

//------

CQColorButton::
CQColorButton(const QString &name, const QColor &c) :
 name_(name), c_(c)
{
  setText(name_);

  QPalette pal = palette();

  pal.setColor(backgroundRole(), c);
  pal.setColor(foregroundRole(), ColorPalette::textColor(c));

  setPalette(pal);

  connect(this, SIGNAL(clicked()), this, SLOT(clickSlot()));
}

void
CQColorButton::
clickSlot()
{
  emit buttonClicked(name_);
}

//------

CQColorLabel::
CQColorLabel(const Type &type) :
 QLabel(), type_(type)
{
  QFontMetrics fm(font());

  setFixedHeight(fm.height() + 4);

  setAutoFillBackground(true);

  setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

void
CQColorLabel::
colorChanged(const QString &name, const QString &id, const QColor &c)
{
  QPalette pal = palette();

  if (type_ == CQColorLabel::BgType) {
    pal.setColor(backgroundRole(), c);
    pal.setColor(foregroundRole(), ColorPalette::textColor(c));
  }
  else {
    pal.setColor(backgroundRole(), QColor(0,0,0,0));
    pal.setColor(foregroundRole(), c);
  }

  setPalette(pal);

  QString str = QString("%1 : %2 %3").arg(name).arg(id).arg(c.name());

  setText(str);

  QFontMetrics fm(font());

  setFixedWidth(fm.width(str) + 32);
}
