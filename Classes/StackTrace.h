#ifdef defined(_WIN32) || defined(WIN32)

#include <Windows.h>

class StackTrace {
	private:
	enum { NFrames = 20 };

	int m_frameCount;
	void* m_frames[NFrames];
	public:
	StackTrace() {
		m_frameCount = CaptureStackBackTrace(1, NFrames, m_frames, NULL);
	}
};

#endif