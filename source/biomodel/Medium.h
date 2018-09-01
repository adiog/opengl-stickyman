// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <bio/Model.h>


namespace bio {
struct Medium
{
    virtual Model getModel() const = 0;
};
}
