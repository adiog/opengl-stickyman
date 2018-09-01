// This file is a part of opengl-stickyman project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include "BoneSequence.h"
#include "opengl/ContextPreserver.h"
#include <vector>
#include <bio/Segment.h>
#include <bio/Sequence.h>
#include <model/Layout.h>


namespace component {
struct Skeleton
{
    template<typename Bones>
    void insertBone(Bones& bones, bio::Segment segment, float length, float ratio)
    {
        bones.emplace(std::make_pair(segment, Bone(segment, length, ratio)));
    }

    Skeleton()
            : pelvis(bio::Segment::Pelvis, 0.3F, 0.5F)
    {
        insertBone(bones, bio::Segment::Chest, 0.60F, 0.7F);
        insertBone(bones, bio::Segment::Head, 0.30F, 0.5F);

        auto &chest = bones.at(bio::Segment::Chest);

        spine.description.emplace_back(bones.at(bio::Segment::Chest));
        spine.description.emplace_back(bones.at(bio::Segment::Head));

        spine.setStartingPoint({0.0, 1.0 + pelvis.getThickness(), 0.0});
        spine.setDirection(-90, {1, 0, 0});

        insertBone(bones, bio::Segment::UpperLegLeft, 0.45F, 0.3F);
        insertBone(bones, bio::Segment::LowerLegLeft, 0.45F, 0.3F);
        insertBone(bones, bio::Segment::FootLeft, 0.25F, 0.3F);

        limbs.emplace(std::make_pair(bio::Sequence::LegLeft, BoneSequence{}));
        auto &leftLeg = limbs.at(bio::Sequence::LegLeft);
        leftLeg.description.emplace_back(bones.at(bio::Segment::UpperLegLeft));
        leftLeg.description.emplace_back(bones.at(bio::Segment::LowerLegLeft));
        leftLeg.description.emplace_back(bones.at(bio::Segment::FootLeft));

        leftLeg.setStartingPoint({-0.15, 1.0, 0});
        leftLeg.setDirection(90, {1, 0, 0});

        insertBone(bones, bio::Segment::UpperLegRight, 0.45F, 0.3F);
        insertBone(bones, bio::Segment::LowerLegRight, 0.45F, 0.3F);
        insertBone(bones, bio::Segment::FootRight, 0.25F, 0.3F);

        limbs.emplace(std::make_pair(bio::Sequence::LegRight, BoneSequence{}));
        auto &legRight = limbs.at(bio::Sequence::LegRight);
        legRight.description.emplace_back(bones.at(bio::Segment::UpperLegRight));
        legRight.description.emplace_back(bones.at(bio::Segment::LowerLegRight));
        legRight.description.emplace_back(bones.at(bio::Segment::FootRight));

        legRight.setStartingPoint({0.15, 1.0, 0});
        legRight.setDirection(90, {1, 0, 0});

        insertBone(bones, bio::Segment::UpperArmLeft, 0.30F, 0.3F);
        insertBone(bones, bio::Segment::ForearmLeft, 0.30F, 0.3F);
        insertBone(bones, bio::Segment::HandLeft, 0.15F, 0.3F);

        limbs.emplace(std::make_pair(bio::Sequence::ArmLeft, BoneSequence{}));
        auto &armLeft = limbs.at(bio::Sequence::ArmLeft);
        armLeft.description.emplace_back(bones.at(bio::Segment::UpperArmLeft));
        armLeft.description.emplace_back(bones.at(bio::Segment::ForearmLeft));
        armLeft.description.emplace_back(bones.at(bio::Segment::HandLeft));

        armLeft.setStartingPoint(
            {-chest.getThickness(), 1.0 + pelvis.getThickness() + chest.getThicknessOffset(), 0});
        armLeft.setDirection(-90, {0, 1, 0});


        insertBone(bones, bio::Segment::UpperArmRight, 0.30F, 0.3F);
        insertBone(bones, bio::Segment::ForearmRight, 0.30F, 0.3F);
        insertBone(bones, bio::Segment::HandRight, 0.15F, 0.3F);

        limbs.emplace(std::make_pair(bio::Sequence::ArmRight, BoneSequence{}));
        auto &armRight = limbs.at(bio::Sequence::ArmRight);
        armRight.description.emplace_back(bones.at(bio::Segment::UpperArmRight));
        armRight.description.emplace_back(bones.at(bio::Segment::ForearmRight));
        armRight.description.emplace_back(bones.at(bio::Segment::HandRight));

        armRight.setStartingPoint(
            {chest.getThickness(), 1.0 + pelvis.getThickness() + chest.getThicknessOffset(), 0});
        armRight.setDirection(90, {0, 1, 0});
    }

    void render(model::Layout & layout)
    {
        {
            ContextPreserver contextPreserver;
            glTranslatef(-0.15F, 1.0F, 0.0F);
            glRotatef(90, 0, 1, 0);
            pelvis.render(layout);
        }

        spine.render(layout);

        for (auto &boneSequenceEntry : limbs)
        {
            boneSequenceEntry.second.render(layout);
        }
    }

    Bone pelvis;
    BoneSequence spine;
    std::unordered_map<bio::Segment, Bone> bones;
    std::unordered_map<bio::Sequence, BoneSequence> limbs;
};
}