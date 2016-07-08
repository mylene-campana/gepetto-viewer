//
//  leaf-node-circle.cpp
//  gepetto-viewer
//
//  Created by Anna Seppala in 2016.
//  Copyright (c) 2016 LAAS-CNRS. All rights reserved.
//

#include <gepetto/viewer/leaf-node-circle.h>

#include <osgUtil/SmoothingVisitor>
#include <osg/CullFace>

namespace graphics {

    /* Declaration of private function members */

    void LeafNodeCircle::init ()
    {
        float radiusCyl = getRadius ();
        float lengthCyl = 0.001;

        /* Create cylinder */
        ::osg::CylinderRefPtr cylinder_shape_ptr = new ::osg::Cylinder();
        cylinder_shape_ptr->set(getPosition () , radiusCyl ,lengthCyl);
        cylinder_shape_ptr->setRotation(getRotation ());

        /* create drawable and add them to geode */
        cylinder_drawable_ = new ::osg::ShapeDrawable( cylinder_shape_ptr );
        geode_ptr_ = new osg::Geode();
        geode_ptr_->addDrawable(cylinder_drawable_);
        /* Create PositionAttitudeTransform */
        this->asQueue()->addChild(geode_ptr_);
        /* Allow transparency */
        geode_ptr_->getOrCreateStateSet()->setMode(GL_BLEND, ::osg::StateAttribute::ON);;
    }


    LeafNodeCircle::LeafNodeCircle(const std::string& name, const osgVector4& color,
            float radius, const osgVector3& pos, const osgQuat& quat): Node(name)
    {
        setRadius(radius);
        setPosition(pos);
        setRotation(quat);
        init();
        setColor(color);
    }

    LeafNodeCircle::LeafNodeCircle(const LeafNodeCircle& other) :
        Node(other.getID())
    {
        init();
      //TODO
    }

    void LeafNodeCircle::initWeakPtr(LeafNodeCircleWeakPtr other_weak_ptr)
    {
        weak_ptr_ = other_weak_ptr;
    }

    /* End of declaration of private function members */

    /* Declaration of protected function members */

    boost::shared_ptr<LeafNodeCircle> LeafNodeCircle::create (const std::string& name,
            const osgVector4& color, float radius, const osgVector3& pos, const osgQuat& quat)
    {
        boost::shared_ptr<LeafNodeCircle> shared_ptr(new LeafNodeCircle(name, color, radius, pos, quat));
        // Add reference to itself
        shared_ptr->initWeakPtr(shared_ptr);
        return shared_ptr;
    }

    boost::shared_ptr<LeafNodeCircle> LeafNodeCircle::createCopy (boost::shared_ptr<LeafNodeCircle> other)
    {
        boost::shared_ptr<LeafNodeCircle> shared_ptr(new LeafNodeCircle(*other));
        // Add reference to itself
        shared_ptr->initWeakPtr(shared_ptr);
        return shared_ptr;
    }

    /* End of declaration of protected function members */

    /* Declaration of public function members */

    boost::shared_ptr<LeafNodeCircle> LeafNodeCircle::clone (void) const
    {
        return LeafNodeCircle::createCopy(weak_ptr_.lock());
    }

    boost::shared_ptr<LeafNodeCircle> LeafNodeCircle::self (void) const
    {
        return weak_ptr_.lock();
    }


    void LeafNodeCircle::setTexture(const std::string& image_path)
    {
      osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
      texture->setDataVariance(osg::Object::DYNAMIC);
      osg::ref_ptr<osg::Image> image = osgDB::readImageFile(image_path);
      if (!image)
      {
        std::cout << " couldn't find texture, quiting." << std::endl;
        return;
      }
      texture->setImage(image);
      geode_ptr_->getStateSet()->setTextureAttributeAndModes(0,texture,osg::StateAttribute::ON);
    }

    osgVector3 LeafNodeCircle::getPosition () const
    {
      return position_;
    }

    osgQuat LeafNodeCircle::getRotation () const
    {
      return rotation_;
    }
    
    void LeafNodeCircle::setPosition (const osgVector3& pos)
    {
      position_ = pos;
    }

    void LeafNodeCircle::setRotation (const osgQuat& rot)
    {
      rotation_ = rot;
    }


    void LeafNodeCircle::setRadius (const float& radius)
    {
        radius_=radius;
    }

    float LeafNodeCircle::getRadius() const
    {
        return radius_;
    }

    void LeafNodeCircle::setColor (const osgVector4& color)
    {
        cylinder_drawable_->setColor(color);
    }

    LeafNodeCircle::~LeafNodeCircle ()
    {
        /* Proper deletion of all tree scene */
        geode_ptr_->removeDrawable(cylinder_drawable_);
        geode_ptr_ = NULL;
        cylinder_drawable_ = NULL;
        weak_ptr_.reset();
    }

    /* End of declaration of public function members */

} /* namespace graphics */

