//
//
//  Created by Justin Carpentier, Mathieu Geisert, Pierre Fernbach in avril 2015.
//  Copyright (c) 2014 LAAS-CNRS. All rights reserved
//

#ifndef SCENEVIEWER_LEAFNODECIRCLE_HH
#define SCENEVIEWER_LEAFNODECIRCLE_HH

#include <gepetto/viewer/node.h>
#include <osgDB/ReadFile>

namespace graphics {

    DEF_CLASS_SMART_PTR(LeafNodeCircle)

    /** Implementation of the Circle GraphicalObject in OSG render */
    class LeafNodeCircle: public Node
    {
    private:
        /** Associated weak pointer */
        LeafNodeCircleWeakPtr weak_ptr_;

        float radius_;
        osgVector3 position_;
        osgQuat rotation_;

        /** axis components : */
        float sizeAxis_;
        ::osg::ShapeDrawableRefPtr cylinder_drawable_;
        /** Associated Geometry (drawable objects)*/
        ::osg::Vec4ArrayRefPtr color_ptr_;

        void init ();


        /* Default constructor */
        LeafNodeCircle(const std::string& name, const osgVector4& color,
                float radius, const osgVector3& pos, const osgQuat& quat);


        /* Copy constructor */
        LeafNodeCircle(const LeafNodeCircle& other);

        /** Initialize weak_ptr */
        void initWeakPtr(LeafNodeCircleWeakPtr other_weak_ptr);


    protected:
    public:
        static LeafNodeCirclePtr_t create(const std::string& name,
                const osgVector4& color, float radius, const osgVector3& pos, const osgQuat& quat);

        /** Static method for creating a clone of box other with the copy constructor
         */
        static LeafNodeCirclePtr_t createCopy(LeafNodeCirclePtr_t other);

        /** Proceed to a clonage of the current object defined by the copy constructor
         */
        virtual LeafNodeCirclePtr_t clone(void) const;

        /** Copy
         \brief Proceed to a copy of the currend object as clone
         */
        virtual NodePtr_t copy() const { return clone(); }

        /** Return a shared pointer of the current object
         */
        LeafNodeCirclePtr_t self(void) const;

        // set color
        void setColor (const osgVector4& color);
        float getRadius() const;
        osgVector3 getPosition () const;
        osgQuat getRotation () const;
        void setPosition (const osgVector3& pos);
        void setRotation (const osgQuat& rot);
        void setRadius (const float& radius);
        void setTexture(const std::string& image_path);

        SCENE_VIEWER_ACCEPT_VISITOR;

        /** Destructor */
        virtual ~LeafNodeCircle();

    };
} /* namespace graphics */

#endif /* SCENEVIEWER_LEAFNODECIRCLE_HH */
