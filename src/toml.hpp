#ifndef toml_h
#define toml_h

#include "animatedWidgets.hpp"
#include "include.h"
#include "slide.hpp"
#include "widget.hpp"
#include <optional>

namespace toml {
  SlideShow* parseSlideShow(toml::table);
  Slide* parseSlide(toml::table);

  // table **required** to have a "type" field
  std::optional<Widget*> parseWidget(toml::table);

  std::optional<Rect*> parseRect(toml::table);
  std::optional<AnimatedRect*> parseAnimatedRect(toml::table);

  std::optional<Spacer*> parseSpacer(toml::table);
  std::optional<AnimatedSpacer*> parseAnimatedSpacer(toml::table);

  std::optional<Circle*> parseCircle(toml::table);
  std::optional<AnimatedCircle*> parseAnimatedCircle(toml::table);

  std::optional<CircleSection*> parseCircleSection(toml::table);
  std::optional<AnimatedCircleSection*> parseAnimatedCircleSection(toml::table);

  std::optional<CircleSectionLines*> parseCircleSectionLines(toml::table);
  std::optional<AnimatedCircleSectionLines*> parseAnimatedCircleSectionLines(toml::table);

  std::optional<Text*> parseText(toml::table);
  std::optional<AnimatedText*> parseAnimatedText(toml::table);
}

#endif
