#include "PrimTriangle.h"
#include "ray.h"
#include "Transform.h"

namespace rt {
	bool CPrimTriangle::intersect(Ray& ray) const
	{
		auto t = MoellerTrumbore(ray);
		if (t) {
			ray.t = t.value().val[0];
			ray.u = t.value().val[1];
			ray.v = t.value().val[2];
			ray.hit = shared_from_this();
			return true;
		}
		else
			return false;
	}

	void CPrimTriangle::transform(const Mat& t)
	{
		// Transform vertexes
		m_a = CTransform::point(m_a, t);
		m_b = CTransform::point(m_b, t);
		m_c = CTransform::point(m_c, t);

		// Transform normals
		Mat t1 = t.inv().t();
		m_normal = normalize(CTransform::vector(m_normal, t1));

		m_edge1 = m_b - m_a;
		m_edge2 = m_c - m_a;
	}
	
	Vec2f CPrimTriangle::getTextureCoords(const Ray& ray) const
	{
		return (1.0f - ray.u - ray.v) * m_ta + ray.u * m_tb + ray.v * m_tc;
	}

	CBoundingBox CPrimTriangle::calcBounds(void) const
	{
		CBoundingBox res;
		res.extend(m_a);
		res.extend(m_b);
		res.extend(m_c);
		return res;
	}
	
	// ---------------------- private ----------------------
	std::optional<Vec3f> CPrimTriangle::MoellerTrumbore(const Ray& ray) const
	{
		const Vec3f pvec = ray.dir.cross(m_edge2);
		const float det = m_edge1.dot(pvec);
		if (fabs(det) < Epsilon)
			return std::nullopt;

		const float inv_det = 1.0f / det;
		const Vec3f tvec = ray.org - m_a;
		float lambda = tvec.dot(pvec);
		lambda *= inv_det;
		if (lambda < 0.0f || lambda > 1.0f)
			return std::nullopt;

		const Vec3f qvec = tvec.cross(m_edge1);
		float mue = ray.dir.dot(qvec);
		mue *= inv_det;
		if (mue < 0.0f || mue + lambda > 1.0f)
			return std::nullopt;

		float t = m_edge2.dot(qvec);
		t *= inv_det;
		if (ray.t <= t || t < Epsilon)
			return std::nullopt;

		return Vec3f(t, lambda, mue);
	}
}

