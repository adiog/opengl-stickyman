// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once


#include <vector>
#include <bio/Segment.h>
#include "BoneSequence.h"

struct Skeleton
{
    Skeleton() {
        bones.emplace(std::make_pair(bio::Segment::Pelvis, Bone(3.0, 0.5)));
        bones.emplace(std::make_pair(bio::Segment::Chest, Bone(4.5, 0.5)));
        bones.emplace(std::make_pair(bio::Segment::Head,  Bone(3.0, 0.5)));

        spine.description.emplace_back(bones.at(bio::Segment::Pelvis));
        spine.description.emplace_back(bones.at(bio::Segment::Chest));
        spine.description.emplace_back(bones.at(bio::Segment::Head));
    }

    void redraw()
    {
        spine.draw();
        for(auto &boneSequence : limbs)
        {
            boneSequence.draw();
        }
    }

    std::unordered_map<bio::Segment, Bone> bones;
    Spine spine;
    std::vector<Limb> limbs;
};
