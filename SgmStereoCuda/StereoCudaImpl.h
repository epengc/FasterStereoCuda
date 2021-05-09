#pragma once
#include "sgm_types.h"

class CostComputor;
class CostAggregator;
class DisparityFilter;
class StereoCudaImpl
{
public:
	StereoCudaImpl();
	~StereoCudaImpl();

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
	bool Init(sint32 width, sint32 height, sint32 min_disparity, sint32 disp_range, CuSGMOption sgm_option, bool print_log = false);

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
	bool Match(uint8* img_left, uint8* img_right, float32* disp_left, float32* disp_right = nullptr, sint16* init_disp_left = nullptr, StereoROI_T* ste_roi_left = nullptr, StereoROI_T* ste_roi_right = nullptr);

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
	bool Init2(sint32 width, sint32 height, sint32 min_disparity, sint32 disp_range, CuSGMOption sgm_option, CamParam_T cam_param, bool print_log = false);

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
	bool Match2(uint8* img_left, uint8* img_right, float32* depth_left, sint16* init_disp_left = nullptr, StereoROI_T* ste_roi_left = nullptr, StereoROI_T* ste_roi_right = nullptr);


	/**
	 * \brief ��ȡ�Ӳ�ͼ��ROI��
	 * \param disp_ptr			�Ӳ�ͼָ��
	 * \param width				�Ӳ�ͼ��
	 * \param height			�Ӳ�ͼ��
	 * \param ste_roi			�����ROI����
	 */
	static void GetRoiFromDispMap(float32* disp_ptr, sint32 width, sint32 height, StereoROI_T& ste_roi);

	/**\brief �ͷ��ڴ� */
	void Release();

	/**\brief ��ȡ��Чֵ */
	static float32 get_invad_float();
	static sint16 get_invad_short();

	/**\brief ��ȡ������ƥ��ģʽ�³���߲�֮������в���Ӳ�������Χ */
	static sint16 get_level_range();

	/**\brief �������˷�����ҳ�ڴ棨������죩 */
	static bool MallocPageLockedPtr(void** ptr, size_t size);

	/**\brief �ͷ���������ҳ�ڴ� */
	static bool FreePageLockedPtr(void* ptr);

#ifdef _DEBUG
	void OutInitValueR(sint16* pInitValue);
#endif

private:
	/**\brief ���ۼ��� */
	bool ComputeCost(uint8* img_left, uint8* img_right, sint16* init_disp_left = nullptr) const;

	/**\brief ���۾ۺ� */
	bool CostAggregate(sint16* init_disp_left = nullptr, StereoROI_T* ste_roi_left = nullptr, StereoROI_T* ste_roi_right = nullptr) const;

	/**\brief �˲� */
	void Filter() const;

	/**\brief �޳�С��ͨ�� */
	void RemovePeaks(StereoROI_T* ste_roi_left, float32* disp_left);

private:
	/**\brief �豸������ָ�� */
	uint8* cu_img_left_;
	uint8* cu_img_right_;
	/**\brief �豸���Ӳ�ͼָ�� */
	float32* cu_disp_out_;
	/**\brief �豸�����ͼָ�� */
	float32* cu_depth_left_;
	/**\brief �豸�˳�ʼ�Ӳ�ͼָ�� */
	sint16* cu_inidisp_left_;
	sint16* cu_inidisp_right_;
	sint16* cu_inidisp_tmp_;

	/**\brief �����˳�ʼ�Ӳ�ͼָ�� */
	sint16* inidisp_tmp_;

	/**\brief sgm���� */
	CuSGMOption sgm_option_;
	/**\brief ������� */
	CamParam_T cam_param_;

	/**\brief ��С�Ӳ�ֵ */
	sint32 min_disparity_;
	/**\brief �ӲΧ */
	sint32 disp_range_;

	/**\brief Ӱ��ߴ� */
	sint32 width_;
	sint32 height_;
	size_t im_psize_;
	size_t dp_psize_;
	size_t idp_psize_;

	/**\brief ���ۼ����� */
	CostComputor* computor_;
	/**\brief ���۾ۺ��� */
	CostAggregator* aggregator_;
	/**\brief �Ӳ�ͼ�˲��� */
	DisparityFilter* filter_;

	/**\brief �������Ӳ�ͼָ�� */
	float32* disp_ptr_;
	/**\brief �޳�С��ͨ�����в����ṹ���� */
	void** remove_peaks_;
	/**\brief �޳�С��ͨ�������߳��� */
	sint32 num_threads_;

	/**\brief �豸���첽�� */
	void* cu_streams_;

	/**\brief ��־��ӡ���� */
	bool print_log_;
};