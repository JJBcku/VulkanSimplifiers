#pragma once

#include "../Include/Common/ListObjectID.h"
#include "SortedListObjectTemplate.h"

namespace VulkanSimplified
{
	constexpr size_t sortedListTemplateDefaultReserve = 0x10;

	template <class T>
	class SortedListTemplate
	{
		static IDType _nextVectorID;

		IDType _nextID;
		IDType _vectorID;
		std::vector<SortedListObjectTemplate<T>> _list;
		std::vector<size_t> _deletedList;

		IDType GetNextId()
		{
			IDType ret = _nextID;
			if (_nextID == std::numeric_limits<IDType>::max())
				throw std::runtime_error("ListTemplate Error: Id system overflowed!");

			_nextID++;
			return ret;
		}

		void ReserveAdditional(size_t add)
		{
			_list.reserve(_list.capacity() + add);
			_deletedList.reserve(_list.capacity() + add);
		}

		void CheckCapacity(size_t add)
		{
			if (_list.capacity() == _list.size())
			{
				if (add == 0)
				{
					ReserveAdditional(_list.capacity());
				}
				else
				{
					ReserveAdditional(add);
				}
			}
		}

		static IDType GetVectorID()
		{
			IDType ret = _nextVectorID;

			if (_nextVectorID == std::numeric_limits<IDType>::max())
				throw std::runtime_error("SortedListTemplate Error: vector id system overflowed!");

			return ret;
		}

	public:
		SortedListTemplate(size_t reserve = 0)
		{
			_nextID = std::numeric_limits<IDType>::lowest();
			_vectorID = GetVectorID();

			if (reserve != 0)
			{
				_list.reserve(reserve);
				_deletedList.reserve(reserve);
			}
			else
			{
				_list.reserve(sortedListTemplateDefaultReserve);
				_deletedList.reserve(sortedListTemplateDefaultReserve);
			}
		}

		~SortedListTemplate()
		{

		}

		SortedListTemplate(const SortedListTemplate&) noexcept = delete;
		SortedListTemplate(SortedListTemplate&&) noexcept = default;

		SortedListTemplate& operator=(const SortedListTemplate&) noexcept = delete;
		SortedListTemplate& operator=(SortedListTemplate&&) noexcept = default;

		size_t GetObjectAmount()
		{
			return _list.size();
		}

		size_t GetFirstUndeleted() const
		{
			size_t ret = _list.size();

			if (!_list.empty() && _list.size() > _deletedList.size())
			{
				size_t check = 0;

				for (size_t i = 0; i < _deletedList.size(); ++i)
				{
					if (check == _deletedList[i])
					{
						check++;
					}
					else
						break;
				}

				ret = check;
			}

			return ret;
		}

		size_t GetNextUndeleted(size_t lastUndeleted) const
		{
			size_t ret = _list.size();

			if (!_list.empty() && lastUndeleted < _list.size() - 1)
			{
				size_t searchedFor = lastUndeleted + 1;
				auto it = std::lower_bound(_deletedList.cbegin(), _deletedList.cend(), searchedFor);

				while (it < _deletedList.cend() && *it == searchedFor)
				{
					it++;
					searchedFor++;
				}

				ret = searchedFor;
				
			}

			return ret;
		}

		size_t GetListSize()
		{
			return _list.size();
		}

		bool GetListEmpty()
		{
			return _list.empty();
		}

		T& GetObjectFromPosition(size_t position)
		{
			if (position >= _list.size())
				throw std::runtime_error("SortedListTemplate::GetObjectFromPosition Error: Program was given an erroneous position!");

			if (!_list[position].HasValue())
				throw std::runtime_error("SortedListTemplate::GetObjectFromPosition Error: Program tried to reference a deleted object!");

			return _list[position].GetObject();
		}

		const T& GetConstObjectFromPosition(size_t position) const
		{
			if (position >= _list.size())
				throw std::runtime_error("SortedListTemplate::GetConstObjectFromPosition Error: Program was given an erroneous position!");

			if (!_list[position].HasValue())
				throw std::runtime_error("SortedListTemplate::GetConstObjectFromPosition Error: Program tried to reference a deleted object!");

			return _list[position].GetConstObject();
		}

		T GetObjectCopyFromPosition(size_t position)
		{
			if (position >= _list.size())
				throw std::runtime_error("SortedListTemplate::GetObjectCopyFromPosition Error: Program was given an erroneous position!");

			if (!_list[position].HasValue())
				throw std::runtime_error("SortedListTemplate::GetObjectCopyFromPosition Error: Program tried to reference a deleted object!");

			return _list[position].GetObjectCopy();
		}

		ListObjectID<T> AddObjectBeforePosition(const T& value, size_t position, size_t add)
		{
			if (position > _list.size())
				throw std::runtime_error("SortedListTemplate::AddObjectBeforePosition Error: Program was given an erroneous position value!");

			ListObjectID<T> ret(GetNextId(), _vectorID);

			if (position == _list.size())
			{
				CheckCapacity(add);
				_list.emplace_back(ret, value);
			}
			else if (position == 0)
			{	
				if (_deletedList.empty())
				{
					CheckCapacity(add);
					_list.insert(_list.cbegin(), SortedListObjectTemplate(ret, value));
				}
				else
				{
					size_t freePosition = _deletedList[0];

					if (freePosition == 0)
					{
						_list[0].ReplaceValue(ret, value);
					}
					else
					{
						size_t currentPosition = freePosition - 1;

						while (freePosition > 0)
						{
							if constexpr (std::is_move_assignable<T>::value)
							{
								_list[freePosition--] = std::move(_list[currentPosition--]);
							}
							else
							{
								_list[freePosition--] = _list[currentPosition--];
							}
							
						}

						_list[0].ReplaceValue(ret, value);
					}

					_deletedList.erase(_deletedList.cbegin());
				}
			}
			else
			{
				size_t insertPosition = position - 1;

				auto it = std::lower_bound(_deletedList.cbegin(), _deletedList.cend(), insertPosition);

				if (it < _deletedList.cend())
				{
					if (*it == insertPosition)
					{
						size_t currentPosition = insertPosition - 1;
						it--;

						while (*it == currentPosition)
						{
							insertPosition--;

							if (it == _deletedList.cbegin())
								break;

							if (currentPosition == 0)
								break;

							currentPosition--;
							it--;
						}

						_list[insertPosition].ReplaceValue(ret, value);
					}
					else
					{
						size_t freePosition = *it;

						size_t currentPosition = freePosition - 1;

						while (freePosition > insertPosition)
						{
							if constexpr (std::is_move_assignable<T>::value)
							{
								_list[freePosition--] = std::move(_list[currentPosition--]);
							}
							else
							{
								_list[freePosition--] = _list[currentPosition--];
							}

						}

						_list[insertPosition].ReplaceValue(ret, value);
					}

					_deletedList.erase(it);
				}
				else
				{
					CheckCapacity(add);
					_list.insert(_list.cbegin() + insertPosition, SortedListObjectTemplate<T>(ret, value));
				}
			}

			return ret;
		}

		ListObjectID<T> AddObjectBeforePosition(T&& value, size_t position, size_t add)
		{
			if (position > _list.size())
				throw std::runtime_error("SortedListTemplate::AddObjectBeforePosition Error: Program was given an erroneous position value!");

			ListObjectID<T> ret(GetNextId(), _vectorID);

			if (position == _list.size())
			{
				CheckCapacity(add);
				_list.emplace_back(ret, std::move(value));
			}
			else if (position == 0)
			{
				if (_deletedList.empty())
				{
					CheckCapacity(add);
					_list.insert(_list.cbegin(), SortedListObjectTemplate(ret, std::move(value)));
				}
				else
				{
					size_t freePosition = _deletedList[0];

					if (freePosition == 0)
					{
						_list[0].ReplaceValue(ret, std::move(value));
					}
					else
					{
						size_t currentPosition = freePosition - 1;

						while (freePosition > 0)
						{
							if constexpr (std::is_move_assignable<T>::value)
							{
								_list[freePosition--] = std::move(_list[currentPosition--]);
							}
							else
							{
								_list[freePosition--] = _list[currentPosition--];
							}

						}

						_list[0].ReplaceValue(ret, std::move(value));
					}

					_deletedList.erase(_deletedList.cbegin());
				}
			}
			else
			{
				size_t insertPosition = position - 1;

				auto it = std::lower_bound(_deletedList.cbegin(), _deletedList.cend(), insertPosition);

				if (it < _deletedList.cend())
				{
					if (*it == insertPosition)
					{
						size_t currentPosition = insertPosition - 1;
						it--;

						while (*it == currentPosition)
						{
							insertPosition--;

							if (it == _deletedList.cbegin())
								break;

							if (currentPosition == 0)
								break;

							currentPosition--;
							it--;
						}

						_list[insertPosition].ReplaceValue(ret, std::move(value));
					}
					else
					{
						size_t freePosition = *it;

						size_t currentPosition = freePosition - 1;

						while (freePosition > insertPosition)
						{
							if constexpr (std::is_move_assignable<T>::value)
							{
								_list[freePosition--] = std::move(_list[currentPosition--]);
							}
							else
							{
								_list[freePosition--] = _list[currentPosition--];
							}

						}

						_list[insertPosition].ReplaceValue(ret, std::move(value));
					}

					_deletedList.erase(it);
				}
				else
				{
					auto insertIt = _list.cbegin();
					std::advance(insertIt, insertPosition);

					CheckCapacity(add);
					_list.insert(insertIt, SortedListObjectTemplate<T>(ret, std::move(value)));
				}
			}

			return ret;
		}

		std::optional<T>& GetObjectOptional(ListObjectID<T> objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("SortedListTemplate GetObject Error: Program tried to get non-existent object!");

			return it->GetObjectOptional();
		}

		const std::optional<T>& GetConstObjectOptional(ListObjectID<T> objectID) const
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("SortedListTemplate GetConstObject Error: Program tried to get non-existent object!");

			return it->GetConstObjectOptional();
		}

		std::optional<T> GetObjectOptionalCopy(ListObjectID<T> objectID) const
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("SortedListTemplate GetObjectCopy Error: Program tried to get non-existent object!");

			return it->GetObjectOptionalCopy();
		}

		T& GetObject(ListObjectID<T> objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("SortedListTemplate GetObject Error: Program tried to get non-existent object!");

			return it->GetObject();
		}

		const T& GetConstObject(ListObjectID<T> objectID) const
		{
			auto it = std::find(_list.cbegin(), _list.cend(), objectID);

			if (it == _list.cend())
				throw std::runtime_error("SortedListTemplate GetObject Error: Program tried to get non-existent object!");

			return it->GetConstObject();
		}

		T GetObjectCopy(ListObjectID<T> objectID) const
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("SortedListTemplate GetObject Error: Program tried to get non-existent object!");

			return it->GetObjectCopy();
		}
	};

	template<class T>
	IDType SortedListTemplate<T>::_nextVectorID = std::numeric_limits<IDType>::lowest();
}
