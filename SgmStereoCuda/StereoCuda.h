#pragma once
#include "sgm_types.h"

#ifdef STEREO_CUDA_EXPORT
#define STEREO_CUDA_DLL __declspec(dllexport)
#else
#define STEREO_CUDA_DLL /*__declspec(dllimport)*/
#endif

class STEREO_CUDA_DLL StereoCuda
{
public:
	StereoCuda();
	~StereoCuda();

public:
	/**
	 * \brief ��ʼ��
	 * \param width				Ӱ���
	 * \param height			Ӱ���
	 * \param min_disparity		��С�Ӳ�ֵ
	 * \param disp_range		�ӲΧ
	 * \param sgm_option		SGM����
	 * \param print_log			�Ƿ��ӡlog��Ϣ
	 * \return true-�ɹ� false-ʧ��
	 */
	bool Init(sint32 width, sint32 height, sint32 min_disparity, sint32 disp_range, CuSGMOption sgm_option,bool print_log = false) const;
	
	/**
	 * \brief ƥ��
	 * \param img_left			��Ӱ������
	 * \param img_right			��Ӱ������
	 * \param disp_left			������Ӳ�ͼ���ߴ���Ӱ��ߴ�һ�£���Ԥ�ȷ����ڴ�
	 * \param disp_right		������Ӳ�ͼ���ߴ���Ӱ��ߴ�һ�£���Ԥ�ȷ����ڴ�
	 * \param init_disp_left	��ʼ�Ӳ�ֵ���飬��Ϊnullptr���򲻲��ó�ʼ�Ӳ�ֵ
	 * \param ste_roi_left		��Ӱ��ROI
	 * \param ste_roi_right		��Ӱ��ROI
	 * \return 
	 */
	bool Match(uint8* img_left, uint8* img_right, float32* disp_left, float32* disp_right = nullptr, sint16* init_disp_left = nullptr, StereoROI_T* ste_roi_left = nullptr, StereoROI_T* ste_roi_right = nullptr) const;

	/**
	 * \brief ��ʼ��2
	 * \param width				Ӱ���			
	 * \param height 			Ӱ���			
	 * \param min_disparity 	��С�Ӳ�ֵ
	 * \param disp_range 		�ӲΧ		
	 * \param sgm_option 		SGM����		
	 * \param cam_param 		�������		
	 * \param print_log 		�Ƿ��ӡlog��Ϣ
	 * \return 
	 */
	bool Init2(sint32 width, sint32 height, sint32 min_disparity, sint32 disp_range, CuSGMOption sgm_option, CamParam_T cam_param, bool print_log = false) const;

	/**
	 * \brief ƥ��2
	 * \param img_left			��Ӱ������		
	 * \param img_right 		��Ӱ������		
	 * \param depth_left 		��Ӱ�����ͼ���ߴ���Ӱ��ߴ�һ�£���Ԥ�ȷ����ڴ�
	 * \param init_disp_left 	��Ӱ���ʼ�Ӳ�ֵ���飬��Ϊnullptr���򲻲��ó�ʼ�Ӳ�ֵ
	 * \param ste_roi_left		��Ӱ��ROI
	 * \param ste_roi_right		��Ӱ��ROI
	 * \return true-�ɹ� false-ʧ��
	 */
	bool Match2(uint8* img_left, uint8* img_right, float32* depth_left, sint16* init_disp_left = nullptr, StereoROI_T* ste_roi_left = nullptr, StereoROI_T* ste_roi_right = nullptr) const;

	/**\brief �ͷ��ڴ� */
	void Release() const;

	/**
	 * \brief ��ȡ�Ӳ�ͼ��ROI��
	 * \param disp_ptr			�Ӳ�ͼָ��
	 * \param width				�Ӳ�ͼ��
	 * \param height			�Ӳ�ͼ��
	 * \param ste_roi			�����ROI����
	 */
	static void GetRoiFromDispMap(float32* disp_ptr, sint32 width, sint32 height, StereoROI_T& ste_roi);

	/**\brief ��ȡ��Чֵ */
	static float32 get_invad_float();
	static sint16 get_invad_short();

	/**\brief ��ȡ������ƥ��ģʽ�³���߲�֮������в���Ӳ�������Χ */
	static sint16 get_level_range();

	/**\brief �������˷�����ҳ�ڴ棨������죩 */
	static bool MallocPageLockedPtr(void** ptr, size_t size);

	/**\brief �ͷ���������ҳ�ڴ� */
	static bool FreePageLockedPtr(void* ptr);
private:
	void* impl_;
};