#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <iostream>

using std::cout;
using std::endl;

// Function to create a pyramid geometry and return its geode
osg::Geode* createPyramid() {
    // Create a new geode and geometry
    auto pyramidGeode = new osg::Geode();
    auto pyramidGeometry = new osg::Geometry();
    pyramidGeode->addDrawable(pyramidGeometry);

    // Create and set the vertices for the pyramid
    auto pyramidVertices = new osg::Vec3Array;
    pyramidVertices->push_back(osg::Vec3(0, 0, 0));
    pyramidVertices->push_back(osg::Vec3(2, 0, 0));
    pyramidVertices->push_back(osg::Vec3(2, 2, 0));
    pyramidVertices->push_back(osg::Vec3(0, 2, 0));
    pyramidVertices->push_back(osg::Vec3(1, 1, 2));

    pyramidGeometry->setVertexArray(pyramidVertices);

    // Create and set the base of the pyramid
    auto pyramidBase = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
    pyramidBase->push_back(3);
    pyramidBase->push_back(2);
    pyramidBase->push_back(1);
    pyramidBase->push_back(0);
    pyramidGeometry->addPrimitiveSet(pyramidBase);
    
    // Create and set the four triangular faces of the pyramid
    for (int index = 0; index < 4; ++index) {
        auto pyramidFace = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
        pyramidFace->push_back(index);
        pyramidFace->push_back((index + 1) % 4);
        pyramidFace->push_back(4);
        pyramidGeometry->addPrimitiveSet(pyramidFace);
    }

    // Set up colors and color bindings for the pyramid geometry
    auto colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(0.0f, 0.0f, 0.5f, 1.0f));
    colors->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f));
    colors->push_back(osg::Vec4(1.0f, 0.5f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(1.0f, 0.0f, 1.0f, 1.0f));

    auto colorIndexArray = new osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType, 4, 4>;
    colorIndexArray->push_back(0);
    colorIndexArray->push_back(1);
    colorIndexArray->push_back(2);
    colorIndexArray->push_back(3);
    colorIndexArray->push_back(0);

    pyramidGeometry->setColorArray(colors);
    pyramidGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

    auto texcoords = new osg::Vec2Array(5);
    (*texcoords)[0].set(0.75f, 0.0f);
    (*texcoords)[1].set(0.50f, 0.0f);
    (*texcoords)[2].set(0.25f, 0.0f);
    (*texcoords)[3].set(0.00f, 0.0f);
    (*texcoords)[4].set(0.50f, 1.0f);
    pyramidGeometry->setTexCoordArray(0, texcoords);

    return pyramidGeode;
}

// Main function setting up the viewer, loading the texture, and creating the scene graph.
int main() {
    osgViewer::Viewer viewer;
    auto root = new osg::Group();

    auto pyramidGeode = createPyramid();
    root->addChild(pyramidGeode);

    auto KLN89FaceTexture = new osg::Texture2D;
    KLN89FaceTexture->setDataVariance(osg::Object::DYNAMIC);

    auto klnFace = osgDB::readImageFile("KLN89FaceB.tga");
    if (!klnFace) {
        cout << "texture not found" << endl;
        return -1;
    }

    KLN89FaceTexture->setImage(klnFace);

    auto stateOne = new osg::StateSet();
    stateOne->setTextureAttributeAndModes(0, KLN89FaceTexture, osg::StateAttribute::ON);

    pyramidGeode->setStateSet(stateOne);

    viewer.setSceneData(root);
    viewer.setCameraManipulator(new osgGA::TrackballManipulator());

    viewer.realize();

    while (!viewer.done()) {
        viewer.frame();
    }

    return 0;
}
