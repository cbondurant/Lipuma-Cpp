#include <catch2/catch.hpp>

#include <QPointF>

#include "catchQtPrintOverrides.hpp"

#include "math/points.hpp"
#include "math/beizer.hpp"


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

TEST_CASE("Beizer Curve implementation", "[math]"){

}