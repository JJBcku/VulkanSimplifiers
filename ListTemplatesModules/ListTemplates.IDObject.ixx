module;

export module ListTemplates.IDObject;

import std;

export typedef std::uint64_t IDType;

export template<class T>
class IDObject
{
private:
	IDType _objectID;
	IDType _vectorID;

public:
	IDObject(IDType objectID = std::numeric_limits<IDType>::max(), IDType vectorID = std::numeric_limits<IDType>::max()) : _objectID(objectID), _vectorID(vectorID) {}
	IDObject(const IDObject& other) = default;
	IDObject(IDObject&& other) noexcept = default;

	IDObject<T>& operator=(const IDObject<T>& other) = default;
	IDObject<T>& operator=(IDObject<T>&&) noexcept = default;

	bool operator==(const IDObject<T>&) const noexcept = default;
	std::strong_ordering operator<=>(const IDObject<T>&) const noexcept = default;
};