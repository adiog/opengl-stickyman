// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <unordered_map>
#include <glm/glm.hpp>
#include <model/Element.h>


namespace model {
using Layout = std::unordered_map<Element, glm::vec3>;
}
