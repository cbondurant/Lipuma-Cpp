//#define CATCH_CONFIG_ENABLE_BENCHMARKING // uncomment if you want to bench the curves, otherwise leave off for faster tests
#include <catch2/catch.hpp>

#include <QPointF>

#include "catchQtPrintOverrides.hpp"

#include "math/points.hpp"
#include "math/bezier.hpp"

TEST_CASE("Consistent Linear interpolation", "[math]"){

	QPointF point(0,0);

	SECTION("0 and 1 should be equal to A and B respectively"){
		REQUIRE(point == Lipuma::lerp(QPointF(100,100), point, 1));
		REQUIRE(point == Lipuma::lerp(point, QPointF(100,100), 0));
	}

	SECTION("Interpolation should be smooth"){
		REQUIRE(point == Lipuma::lerp(QPointF(-5,-5), QPointF(5,5), 0.5));
	}

	SECTION("Values outside of bounds should linearly extrapolate"){
		REQUIRE(point == Lipuma::lerp(QPointF(-10,0), QPointF(-5,0), 2));
	}
}

TEST_CASE("Vector Normalization", "[math]"){
	QPointF point(10,0);

	SECTION("Length of a normalized Vector should be 1"){
		REQUIRE(1 == Lipuma::distance(Lipuma::normalize(point)));
	}

	SECTION("Normalization of a null vector (0,0) should return (0,0)"){
		REQUIRE(QPoint() == Lipuma::normalize(QPoint()));
	}

	SECTION("Normalization should be lossless"){
		QPointF iter(100,0);
		QPointF iter1 = Lipuma::normalize(iter);
		for (int i = 0; i < 1000; ++i){
			iter = Lipuma::normalize(iter);
		}
		REQUIRE(iter == iter1);
	}
}

TEST_CASE("Vector Distance", "[math]"){

	// Vertical, horizontal, and 45-degree vectors
	auto point = GENERATE(QPointF(-1,0), QPointF(0,-1), QPointF(1,0), QPointF(0,1), QPointF(sqrt(0.5), sqrt(0.5)));
	SECTION("Distance is accurate at multiple angles"){
		REQUIRE(1 == Lipuma::distance(point));
	}

	SECTION("Distance does not fail when the vector is 0"){
		REQUIRE(Lipuma::distance(QPointF()) == 0);
	}
}

TEST_CASE("Bezier Curve implementation", "[math]"){
	QPointF start {0,0};
	QPointF end {15,0};
	auto curve = Lipuma::BezierCurve(start, QPointF(5,5),QPointF(10, 5), end);

	int x = GENERATE(2,3,4,5,10,20,50,100);
	SECTION("Generating a Beizer curve iterator with N returns N points", "[math]"){
		std::vector<QPointF> v;
		for (auto i = curve.sweepCurveIterator(x); !i->isEmpty(); i->advance()){
			v.emplace(v.end(), i->getPointTangent().point);
		}
		REQUIRE(v.size() == x);
		v.clear();
		for (auto i = curve.sweepLinearCurveIterator(x); !i->isEmpty(); i->advance()){
			v.emplace(v.end(), i->getPointTangent().point);
		}
		REQUIRE(v.size() == x);
	}

	SECTION("The first point of an iterator should be equal to the start point","[math]"){
		auto i = curve.sweepCurveIterator(x);
		REQUIRE(i->getPointTangent().point==start);
		i = curve.sweepLinearCurveIterator(x);
		REQUIRE(i->getPointTangent().point==start);
	}

	SECTION("Point (0) should be equal to start and Point(1) equal to end"){
		REQUIRE(curve.getPoint(0) == start);
		REQUIRE(curve.getPoint(1) == end);
	}

	SECTION("Beginning and end of iterators should be equal to the start and end of curve", "[math]"){
		auto i = curve.sweepCurveIterator(x);
		REQUIRE(i->getPointTangent().point == start);
		Lipuma::PointTangent prevPt;
		while (!i->isEmpty()){
			prevPt = i->getPointTangentAdvance();
		}
		REQUIRE(prevPt.point == end);

		auto j = curve.sweepLinearCurveIterator(x);
		REQUIRE(j->getPointTangent().point == start);
		while (!j->isEmpty()){
			prevPt = j->getPointTangentAdvance();
		}
		REQUIRE(prevPt.point == end);
	}

}