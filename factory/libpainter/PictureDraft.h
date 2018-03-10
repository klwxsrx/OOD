#pragma once
#include "IPictureDraft.h"

class CPictureDraft : public IPictureDraft
{

public:

	CPictureDraft();

	void AddShape(std::unique_ptr<IShape> && shape) override;
	bool IsEmpty()const override;

	ConstIterator begin()const override;
	ConstIterator end()const override;

	CPictureDraft(CPictureDraft &&) = default;
	CPictureDraft& operator=(CPictureDraft &&) = default;

	CPictureDraft(const CPictureDraft &) = delete;
	CPictureDraft& operator=(const CPictureDraft &) = delete;
private:
	Storage m_shapes;
};

inline CPictureDraft::ConstIterator begin(const CPictureDraft & draft)
{
	return draft.begin();
}

inline CPictureDraft::ConstIterator end(const CPictureDraft & draft)
{
	return draft.end();
}