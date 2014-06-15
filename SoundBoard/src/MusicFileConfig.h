#pragma once

class MusicFileConfig
{
private:
	float min_freq_;
	float max_freq_;
	float sheet_size_;
public:
	MusicFileConfig() {}
	~MusicFileConfig() {}

	void setMinFrq(float min_freq);
	void setMaxFrq(float max_freq);
	void setSheetSize(float sheet_size);
	float minFrq() { return min_freq_; }
	float maxFrq() { return max_freq_; }
	float sheetSize() { return sheet_size_; }
};