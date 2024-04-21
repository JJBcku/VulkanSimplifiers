#pragma once

#include "../Include/Common/ListObjectID.h"

namespace VulkanSimplified
{
	template<class T>
	class ListObjectTemplate
	{
		ListObjectID<T> _objectID;
		std::optional<T> _object;
		char _padding[16 - (sizeof(_object) % 8)];

		void ThrowOnHasValue()
		{
			if (_object.has_value())
				throw std::runtime_error("ListObjectTemplate Error: Program tried to replace existing value");
		}

	public:

		ListObjectTemplate(const ListObjectID<T>& objectID, const T& object) noexcept : _objectID(objectID), _object(object)
		{
			memset(_padding, 0, sizeof(_padding));
		}

		ListObjectTemplate(const ListObjectID<T>& objectID, T&& object) noexcept : _objectID(objectID), _object(std::move(object))
		{
			memset(_padding, 0, sizeof(_padding));
		}

		ListObjectTemplate(const ListObjectTemplate<T>& other) noexcept : _objectID(other._objectID), _object(other._object)
		{
			memset(_padding, 0, sizeof(_padding));
		}

		ListObjectTemplate(ListObjectTemplate<T>&& other) noexcept : _objectID(std::move(other._objectID)), _object(std::move(other._object))
		{
			memset(_padding, 0, sizeof(_padding));
		}

		ListObjectTemplate<T>& operator=(const ListObjectTemplate<T>& other)
		{
			_objectID = other._objectID;
			_object = other._object;
		}

		ListObjectTemplate<T>& operator=(ListObjectTemplate<T>&& other)
		{
			_objectID = std::move(other._objectID);
			_object = std::move(other._object);
		}

		void ReplaceValue(const ListObjectID<T>& objectID, const T& object)
		{
			ThrowOnHasValue();

			_object = object;
			_objectID = objectID;
		}

		void ReplaceValue(const ListObjectID<T>& objectID, T&& object)
		{
			ThrowOnHasValue();

			_object = std::move(object);
			_objectID = objectID;
		}

		ListObjectID<T> GetObjectID() const { return _objectID; }

		std::optional<T>& GetObjectOptional() { return _object; }
		const std::optional<T>& GetConstObjectOptional() const { return _object; }
		std::optional<T> GetObjectOptionalCopy() const { return _object; }

		T& GetObject() { assert(_object.has_value()); return _object.value(); }
		const T& GetConstObject() const { assert(_object.has_value()); return _object.value(); }
		T GetObjectCopy() const { assert(_object.has_value()); return _object.value(); }

		bool HasValue() const { return _object.has_value(); }

		void DeleteObject() { _object.reset(); }

		bool operator==(bool has_value) const { return _object.has_value() == has_value; }
		bool operator==(const ListObjectID<T>& ID) const { return ID == _objectID; }

		std::strong_ordering operator<=>(const ListObjectTemplate<T>&) const noexcept = default;
		bool operator==(const ListObjectTemplate<T>&) const noexcept = default;

		bool operator==(const T& other) const noexcept
		{
			if (!_object.has_value())
			{
				return false;
			}
			else
			{
				return _object.value() == other;
			}
		}

		bool operator==(const std::optional<T>& other) const noexcept
		{
			return _object == other;
		}
	};
}