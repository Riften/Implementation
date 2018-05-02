#pragma once
#include "ray.h"
#include "light.h"
#include "material.h"
#define mini 0.001

/*
Implementation of rendering pipeline:
Input a ray:
	for all the objects in the scene
		get the intersection that is closest to the origin of ray
	for all the lights in the scene
		compute the color of intersection lighted by these lights
		merge these color together
	if reflective:
		generate a reflected ray and rendering recursively
		merge color
	return color
*/
Color rend(Ray& ray, objUnion& scene, lightUnion& lights, bool isRef = false, int maxReflect = 0) {

	Intersection result = scene.intersect(ray);
	if (result.isHit == 0) {
		return Color::black();
	}
	Color color = lights.intersect(scene, result);
	if (isRef && maxReflect > mini)
	{
		float reflectivity = result.object->material->getRef();
		GVector3 r = result.normal*(-2 * result.normal.dotMul(ray.getDirection())) + ray.getDirection();
		Ray reflectRay = Ray(result.position, r);
		Color reflectedColor = rend(reflectRay, scene, lights, isRef, maxReflect - 1);
		color = color.add(reflectedColor.multiply(reflectivity));
	}
	return color;
}

