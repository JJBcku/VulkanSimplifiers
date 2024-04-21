#pragma once

#include "../Include/Common/ListObjectID.h"

namespace VulkanSimplified
{
	template<class T>
	class SortedListObjectTemplate
	{
		ListObjectID<T> _objectID;
		std::optional<T> _object;
		char _padding[16 - (sizeof(_object) % 8)];

		void ThrowOnHasValue()
		{
			if (_object.has_value())
				throw std::runtime_error("SortedListObjectTemplate Error: Program tried to replace existing value");
		}

	public:
		SortedListObjectTemplate(const ListObjectID<T>& objectID, const T& object) noexcept : _objectID(objectID), _object(object)
		{
			memset(_padding, 0, sizeof(_padding));
		}

		SortedListObjectTemplate(const ListObjectID<T>& objectID, T&& object) noexcept : _objectID(objectID), _object(std::move(object))
		{
			memset(_padding, 0, sizeof(_padding));
		}

		SortedListObjectTemplate(const SortedListObjectTemplate<T>& other) noexcept : _objectID(other._objectID), _object(other._object)
		{
			memset(_padding, 0, sizeof(_padding));
		}

		SortedListObjectTemplate(SortedListObjectTemplate<T>&& other) noexcept : _objectID(std::move(other._objectID)), _object(std::move(other._object))
		{
			memset(_padding, 0, sizeof(_padding));
		}

		SortedListObjectTemplate<T>& operator=(const SortedListObjectTemplate<T>& other) noexcept
		{
			_objectID = other._objectID;
			_object = other._object;

			return *this;
		}

		SortedListObjectTemplate<T>& operator=(SortedListObjectTemplate<T>&& other) noexcept
		{
			_objectID = std::move(other._objectID);
			_object = std::move(other._object);

			return *this;
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

		T& GetObject()
		{
			if (!_object.has_value())
			{
				throw std::runtime_error("SortedListObjectTemplate GetObject Error: Program tried to access a deleted object");
			}
			else
				return _object.value();
		}

		const T& GetConstObject() const
		{
			if (!_object.has_value())
			{
				throw std::runtime_error("SortedListObjectTemplate GetConstObject Error: Program tried to access a deleted object");
			}
			else
				return _object.value();
		}

		T GetObjectCopy() const
		{
			if (!_object.has_value())
			{
				throw std::runtime_error("SortedListObjectTemplate GetObjectCopy Error: Program tried to access a deleted object");
			}
			else
				return _object.value();
		}

		bool HasValue() const noexcept { return _object.has_value(); }

		void DeleteObject() noexcept { _object.reset(); }

		bool operator==(bool has_value) const noexcept { return _object.has_value() == has_value; }
		bool operator==(const ListObjectID<T>& ID) const noexcept { return ID == _objectID; }

		std::strong_ordering operator<=>(const SortedListObjectTemplate<T>& other) const noexcept
		{
			if (_object != other._object)
				return _object <=> other._object;
			else
				return _objectID <=> other._objectID;
		}

		bool operator==(const SortedListObjectTemplate<T>& other) const noexcept
		{
			if (_object != other._object)
				return false;
			else
				return _objectID == other._objectID;
		}
	};
}
