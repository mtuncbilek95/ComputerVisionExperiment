#pragma once

#include <cstdint>
#include <cmath>
#include <concepts>
#include <type_traits>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef size_t usize;

typedef float f32;
typedef double f64;

constexpr u64 u64_max = 0xFFFFFFFFFFFFFFFF;
constexpr u32 u32_max = 0xFFFFFFFF;
constexpr u16 u16_max = 0xFFFF;
constexpr u8 u8_max = 0xFF;

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

namespace Math
{
	constexpr f64 Pi = 3.14159265358979323846;

	template<Arithmetic T>
	using Vec2 = glm::tvec2<T>;

	template<Arithmetic T>
	using Vec3 = glm::tvec3<T>;

	template<Arithmetic T>
	using Vec4 = glm::tvec4<T>;

	template<Arithmetic T>
	using Mat2 = glm::tmat2x2<T>;

	template<Arithmetic T>
	using Mat3 = glm::tmat3x3<T>;

	template<Arithmetic T>
	using Mat4 = glm::tmat4x4<T>;

	using Vec2uc = Vec2<u8>;
	using Vec3uc = Vec3<u8>;
	using Vec4uc = Vec4<u8>;

	using Vec2f = Vec2<f32>;
	using Vec3f = Vec3<f32>;
	using Vec4f = Vec4<f32>;

	using Vec2d = Vec2<f64>;
	using Vec3d = Vec3<f64>;
	using Vec4d = Vec4<f64>;

	using Vec2i = Vec2<i32>;
	using Vec3i = Vec3<i32>;
	using Vec4i = Vec4<i32>;

	using Vec2u = Vec2<u32>;
	using Vec3u = Vec3<u32>;
	using Vec4u = Vec4<u32>;

	using Mat2f = Mat2<f32>;
	using Mat3f = Mat3<f32>;
	using Mat4f = Mat4<f32>;

	using Mat2d = Mat2<f64>;
	using Mat3d = Mat3<f64>;
	using Mat4d = Mat4<f64>;
}