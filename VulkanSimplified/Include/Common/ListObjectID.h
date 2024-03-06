#pragma once

namespace VulkanSimplified
{
	using IDType = uint64_t;

	template<class T>
	class ListObjectID
	{
		IDType _objectID;
		IDType _vectorID;

	public:
		ListObjectID(IDType objectID = std::numeric_limits<IDType>::max(), IDType vectorID = std::numeric_limits<IDType>::max()) : _objectID(objectID), _vectorID(vectorID) {}
		ListObjectID(const ListObjectID& other) = default;
		ListObjectID(ListObjectID&& other) noexcept = default;

		ListObjectID<T>& operator=(const ListObjectID<T>& other) = default;
		ListObjectID<T>& operator=(ListObjectID<T>&&) noexcept = default;

		bool operator==(const ListObjectID<T>& other) const noexcept = default;
		std::strong_ordering operator<=>(const ListObjectID<T>&) const noexcept = default;
	};
}
