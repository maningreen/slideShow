#include "toml.hpp"
#include "image.hpp"
#include "include.h"
#include "slide.hpp"
#include "widget.hpp"
#include "animatedWidgets.hpp"

#include <optional>
#include <vector>

std::string lower(std::string s) {
  for(char* c = s.data(); c < s.data() + s.length(); c++) 
    *c = std::tolower(*c);
  return s;
}

std::optional<AnimatedWidget::easeType> strToAnimation(std::string x) {
  if(x == "In")
    return AnimatedWidget::In;
  else if(x == "Out")
    return AnimatedWidget::Out;
  else if(x == "InOut")
    return AnimatedWidget::InOut;
  else
    return std::nullopt;
}

// returns Horizontal as a default if unable to parse.
Orientation strToOrientation(std::string x) {
  x = lower(x);
  if(x == "vertical") return Vertical;
  else return Horizontal;
}

std::optional<Direction> strToDir(std::string x) {
  x = lower(x);
  if(x == "up") return Up;
  else if(x == "down") return Down;
  else if(x == "left") return Left;
  else if(x == "right") return Right;
  else return std::nullopt;
}

Slide* toml::parseSlide(toml::table x) {
  Slide* slide = new Slide;
  if(toml::array* widgets = x["widgets"].as_array()) {
    widgets->for_each([&](toml::node& el){
      if(toml::table* table = el.as_table())
        if(std::optional<Widget*> n = parseWidget(*table))
          slide->widgets.push_back(n.value());
    });
  }
  return slide;
}

fontType strToFontType(std::string x) {
  if(x == "header") 
  return body;
}

std::optional<Widget*> toml::parseWidget(toml::table table) {
  std::optional<std::string> type = table["type"].value<std::string>();
  if(!type)
    return std::nullopt;
  else if(type == "rect")
    return parseRect(table);
  else if(type == "animatedRect")
    return parseAnimatedRect(table);
  else if(type == "spacer")
    return parseSpacer(table);
  else if(type == "animatedSpacer")
    return parseAnimatedSpacer(table);
  else if(type == "circle")
    return parseCircle(table);
  else if(type == "animatedCircle")
    return parseAnimatedCircle(table);
  else if(type == "circleSection")
    return parseCircleSection(table);
  else if(type == "animatedCircleSection")
    return parseAnimatedCircleSection(table);
  else if(type == "circleSectionLines")
    return parseCircleSectionLines(table);
  else if(type == "animatedCircleSectionLines")
    return parseAnimatedCircleSectionLines(table);
  else if(type == "text")
    return parseText(table);
  else if(type == "animatedText")
    return parseAnimatedText(table);
  else if(type == "box")
    return parseBox(table);
  else if(type == "image")
    return parseImage(table);
  else if(type == "animatedImage")
    return parseAnimatedImage(table);
  else return std::nullopt;
}

std::vector<Widget*> parseChildenThingy(toml::table x) {
  std::vector<Widget*> y;
  if(toml::array* widgets = x["children"].as_array()) {
    widgets->for_each([&](toml::node& el){
      if(toml::table* table = el.as_table())
        if(std::optional<Widget*> n = parseWidget(*table))
          y.push_back(n.value());
    });
  }
  return y;
}

std::optional<Rect*> toml::parseRect(toml::table table) {
  std::optional<std::string> colourM = table["colour"].value<std::string>();
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();
  std::optional<float> widthM = table["width"].value<float>();
  std::optional<float> heightM = table["height"].value<float>();
  std::vector<Widget*> kids;
  if(!(colourM && xM && yM && widthM && heightM))
    return std::nullopt;
  else
    return new Rect(xM.value(), yM.value(), widthM.value(), heightM.value(), hexToCol(colourM.value()));
}

std::optional<AnimatedRect*> toml::parseAnimatedRect(toml::table table) {
  std::optional<std::string> colourM = table["colour"].value<std::string>();
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();
  std::optional<float> widthM = table["width"].value<float>();
  std::optional<float> heightM = table["height"].value<float>();
  std::optional<std::string> typeM = table["easeType"].value<std::string>();
  std::optional<std::string> orientationM = table["orientation"].value<std::string>();
  if(!(colourM && xM && yM && widthM && heightM))
    return std::nullopt;

  float speed = table["speed"].value<float>().value_or(1);
  Direction orientation = strToDir(orientationM->data()).value_or(Down);
  AnimatedWidget::easeType type = strToAnimation(typeM.value_or("InOut")).value();

  AnimatedRect* rect = new AnimatedRect(Rect(xM.value(), yM.value(), widthM.value(), heightM.value(), hexToCol(colourM.value())), type, orientation);
  rect->entities = parseChildenThingy(table);
  rect->speed = speed;

  return rect;
}

std::optional<Spacer*> toml::parseSpacer(toml::table table) {
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();
  std::optional<float> widthM = table["width"].value<float>();
  std::optional<float> heightM = table["height"].value<float>();
  if(!(xM && yM && widthM && heightM))
    return std::nullopt;
  else 
    return new Spacer(xM.value(), yM.value(), widthM.value(), heightM.value());
}

std::optional<AnimatedSpacer*> toml::parseAnimatedSpacer(toml::table table) {
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();
  std::optional<float> widthM = table["width"].value<float>();
  std::optional<float> heightM = table["height"].value<float>();
  std::optional<std::string> orientationM = table["orientation"].value<std::string>();
  if(!(xM && yM && widthM && heightM))
    return std::nullopt;

  float speed = table["speed"].value<float>().value_or(1);
  Direction orientation = strToDir(orientationM->data()).value_or(Up);
  AnimatedWidget::easeType type = strToAnimation(table["easeType"].value_or("InOut")).value();

  AnimatedSpacer* x = new AnimatedSpacer(Spacer(xM.value(), yM.value(), widthM.value(), heightM.value()), type, orientation);
  x->entities = parseChildenThingy(table);
  x->speed = speed;
  return x;
}

std::optional<Circle*> toml::parseCircle(toml::table table) {
  std::optional<std::string> colourS = table["colour"].value<std::string>();
  std::optional<float> radiusM = table["radius"].value<float>();
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();

  if(!(colourS && radiusM && xM && yM))
    return std::nullopt;
  return new Circle(xM.value(), yM.value(), radiusM.value(), hexToCol(colourS.value()));
}

std::optional<AnimatedCircle*> toml::parseAnimatedCircle(toml::table table) {
  std::optional<std::string> colourS = table["colour"].value<std::string>();
  std::optional<float> radiusM = table["radius"].value<float>();
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();

  AnimatedWidget::easeType easeType = strToAnimation(table["easeType"].value_or("InOut")).value();

  if(!(colourS && radiusM && xM && yM))
    return std::nullopt;

  float speed = table["speed"].value<float>().value_or(1);

  AnimatedCircle* x = new AnimatedCircle(Circle(xM.value(), yM.value(), radiusM.value(), hexToCol(colourS.value())), easeType);
  x->entities = parseChildenThingy(table);
  x->speed = speed;
  return x;
}

std::optional<CircleSection*> toml::parseCircleSection(toml::table table) {
  std::optional<std::string> colourS = table["colour"].value<std::string>();
  std::optional<float> radiusM = table["radius"].value<float>();
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();
  std::optional<float> centerAngle = table["centerAngle"].value<float>();
  std::optional<float> offsetAngle = table["offsetAngle"].value<float>();

  if(!(colourS && radiusM && xM && yM && centerAngle && offsetAngle))
    return std::nullopt;
  return new CircleSection(
    {
      xM.value(),
      yM.value()
    },
    radiusM.value(),
    DEG2RAD * centerAngle.value(),
    DEG2RAD * offsetAngle.value(),
    hexToCol(colourS.value())
  );
}

std::optional<AnimatedCircleSection*> toml::parseAnimatedCircleSection(toml::table table) {
  AnimatedWidget::easeType easeType = strToAnimation(table["easeType"].value_or("InOut")).value();

  std::optional<std::string> colourS = table["colour"].value<std::string>();
  std::optional<float> radiusM = table["radius"].value<float>();
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();
  std::optional<float> centerAngle = table["centerAngle"].value<float>();
  std::optional<float> offsetAngle = table["offsetAngle"].value<float>();

  if(!(colourS && radiusM && xM && yM && centerAngle && offsetAngle))
    return std::nullopt;

  float speed = table["speed"].value<float>().value_or(1);

  AnimatedCircleSection* x = new AnimatedCircleSection(
      CircleSection(
        {
          xM.value(),
          yM.value()
        },
        radiusM.value(),
        DEG2RAD * centerAngle.value(),
        DEG2RAD * offsetAngle.value(),
        hexToCol(colourS.value())
      ),
    easeType
  );
  x->entities = parseChildenThingy(table);
  x->speed = speed;
  return x;
}

std::optional<CircleSectionLines*> toml::parseCircleSectionLines(toml::table table) {
  std::optional<std::string> colourS = table["colour"].value<std::string>();
  std::optional<float> radiusM = table["radius"].value<float>();
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();
  std::optional<float> centerAngle = table["centerAngle"].value<float>();
  std::optional<float> offsetAngle = table["offsetAngle"].value<float>();
  std::optional<float> thicknessM = table["thickness"].value<float>();

  if(!(colourS && radiusM && xM && yM && centerAngle && offsetAngle && thicknessM))
    return std::nullopt;
  return new CircleSectionLines(
    {
      xM.value(),
      yM.value()
    },
    radiusM.value(),
    DEG2RAD * centerAngle.value(),
    DEG2RAD * offsetAngle.value(),
    thicknessM.value(),
    hexToCol(colourS.value())
  );
}

std::optional<AnimatedCircleSectionLines*> toml::parseAnimatedCircleSectionLines(toml::table table) {
  AnimatedWidget::easeType easeType = strToAnimation(table["easeType"].value_or("InOut")).value();

  std::optional<std::string> colourS = table["colour"].value<std::string>();
  std::optional<float> radiusM = table["radius"].value<float>();
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();
  std::optional<float> centerAngle = table["centerAngle"].value<float>();
  std::optional<float> offsetAngle = table["offsetAngle"].value<float>();
  std::optional<float> thicknessM = table["thickness"].value<float>();

  if(!(colourS && radiusM && xM && yM && centerAngle && offsetAngle && thicknessM))
    return std::nullopt;

  float speed = table["speed"].value<float>().value_or(1);

  AnimatedCircleSectionLines* x = new AnimatedCircleSectionLines(
      CircleSectionLines(
        {
          xM.value(),
          yM.value()
        },
        radiusM.value(),
        DEG2RAD * centerAngle.value(),
        DEG2RAD * offsetAngle.value(),
        thicknessM.value(),
        hexToCol(colourS.value())
      ),
    easeType
  );
  x->entities = parseChildenThingy(table);
  x->speed = speed;
  return x;
}

std::optional<Text*> toml::parseText(toml::table table) {
  std::optional<std::string> colourM = table["colour"].value<std::string>();
  std::optional<std::string> contentsM = table["contents"].value<std::string>();
  std::optional<float> sizeM = table["size"].value<float>();
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();
  std::optional<float> demsXM = table["dimensionsX"].value<float>();
  std::optional<float> demsYM = table["dimensionsY"].value<float>();
  std::optional<std::string> type = table["fontType"].value<std::string>();

  if(!(colourM && contentsM && sizeM && xM && yM))
    return std::nullopt;
  return new Text(
    contentsM.value(), 
    strToFontType(type.value_or("")), 
    sizeM.value(), 
    {
      xM.value(),
      yM.value()
    },
    {
      demsXM.value_or(0),
      demsYM.value_or(0)
    },
    hexToCol(colourM.value()));
}

std::optional<AnimatedText*> toml::parseAnimatedText(toml::table table) {
  std::optional<std::string> colourM = table["colour"].value<std::string>();
  std::optional<std::string> contentsM = table["contents"].value<std::string>();
  std::optional<float> sizeM = table["size"].value<float>();
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();
  std::optional<float> demsXM = table["dimensionsX"].value<float>();
  std::optional<float> demsYM = table["dimensionsY"].value<float>();
  std::optional<std::string> type = table["fontType"].value<std::string>();
  float speed = table["speed"].value<float>().value_or(1);
  AnimatedWidget::easeType easeType = strToAnimation(table["easeType"].value_or("InOut")).value();

  if(!(colourM && contentsM && sizeM && xM && yM))
    return std::nullopt;
  AnimatedText* x = new AnimatedText(Text(
    contentsM.value(), 
    strToFontType(type.value_or("")), 
    sizeM.value(), 
    {
      xM.value(),
      yM.value()
    },
    {
      demsXM.value_or(0),
      demsYM.value_or(0)
    }, hexToCol(colourM.value())), easeType);
  x->entities = parseChildenThingy(table);
  x->speed = speed;
  return x;
}

SlideShow* toml::parseSlideShow(toml::table x) {
  SlideShow* show = new SlideShow((std::vector<Slide>){});
  if(toml::array* y = x["slides"].as_array())
    y->for_each([&](toml::node& el){
      if(el.is_table()) show->addSlide(parseSlide(*el.as_table()));
    });
  return show;
}

Box* toml::parseBox(toml::table x) {
  Orientation d = strToOrientation(x["orientation"].value<std::string>().value_or("horizontal"));
  Box* b = new Box(d, {});
  b->position = {
    x["x"].value<float>().value_or(0),
    x["y"].value<float>().value_or(0)
  };
  if(toml::array* widgets = x["widgets"].as_array()) {
    widgets->for_each([b](toml::node& x){
      if(toml::table* table = x.as_table())
        if(std::optional<Widget*> n = parseWidget(*table))
          b->entities.push_back(n.value());
    });
  }
  return b;
}

std::optional<ImageWidget*> toml::parseImage(toml::table table) {
  std::optional<std::string> source = table["source"].value<std::string>();
  std::optional<float> x = table["x"].value<float>();
  std::optional<float> y = table["y"].value<float>();

  if(!(source && x && y))
    return std::nullopt;
  return new ImageWidget(source.value(), {x.value(), y.value()});
}

std::optional<AnimatedImageWidget*> toml::parseAnimatedImage(toml::table table) {
  std::optional<std::string> sourceM = table["source"].value<std::string>();
  std::optional<float> xM = table["x"].value<float>();
  std::optional<float> yM = table["y"].value<float>();

  if(!(sourceM && xM && yM))
    return std::nullopt;

  Direction dir = strToDir(table["direction"].value_or("")).value_or(Up);
  AnimatedWidget::easeType type = strToAnimation(table["direction"].value_or("")).value_or(AnimatedWidget::InOut);
  AnimatedImageWidget* x = new AnimatedImageWidget(ImageWidget(sourceM.value(), {xM.value(), yM.value()}), type, dir);
  UnloadTexture(x->source);
  Image image = LoadImage(sourceM.value().c_str());
  x->source = LoadTextureFromImage(image);
  UnloadImage(image);
  x->entities = parseChildenThingy(table);
  return x;
}
