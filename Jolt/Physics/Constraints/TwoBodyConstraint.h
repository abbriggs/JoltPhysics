// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

#include <Jolt/Physics/Constraints/Constraint.h>
#include <Jolt/Physics/Body/Body.h>

namespace JPH {

class TwoBodyConstraint;

/// Base class for settings for all constraints that involve 2 bodies
class TwoBodyConstraintSettings : public ConstraintSettings
{
public:
	JPH_DECLARE_SERIALIZABLE_ABSTRACT(TwoBodyConstraintSettings)

	/// Create an an instance of this constraint
	/// You can use Body::sFixedToWorld for inBody1 if you want to attach inBody2 to the world
	virtual TwoBodyConstraint *	Create(Body &inBody1, Body &inBody2) const = 0;
};

/// Base class for all constraints that involve 2 bodies. Body1 is usually considered the parent, Body2 the child.
class TwoBodyConstraint : public Constraint
{
public:
	/// Constructor
								TwoBodyConstraint(Body &inBody1, Body &inBody2, const TwoBodyConstraintSettings &inSettings) : Constraint(inSettings), mBody1(&inBody1), mBody2(&inBody2) { }

	/// Solver interface
	virtual bool				IsActive() const override				{ return Constraint::IsActive() && (mBody1->IsActive() || mBody2->IsActive()) && (mBody2->IsDynamic() || mBody1->IsDynamic()); }
#ifdef JPH_DEBUG_RENDERER
	virtual void				DrawConstraintReferenceFrame(DebugRenderer *inRenderer) const override;
#endif // JPH_DEBUG_RENDERER

	/// Access to the connected bodies
	Body *						GetBody1() const						{ return mBody1; }
	Body *						GetBody2() const						{ return mBody2; }

	/// Calculates the transform that transforms from constraint space to body 1 space. The first column of the matrix is the primary constraint axis (e.g. the hinge axis / slider direction), second column the secondary etc.
	virtual Mat44				GetConstraintToBody1Matrix() const = 0;

	/// Calculates the transform that transforms from constraint space to body 2 space. The first column of the matrix is the primary constraint axis (e.g. the hinge axis / slider direction), second column the secondary etc.
	virtual Mat44				GetConstraintToBody2Matrix() const = 0;

	/// Link bodies that are connected by this constraint in the island builder
	virtual void				BuildIslands(uint32 inConstraintIndex, IslandBuilder &ioBuilder, BodyManager &inBodyManager) override;

protected:
	/// The two bodies involved
	Body *						mBody1;
	Body *						mBody2;
};

} // JPH