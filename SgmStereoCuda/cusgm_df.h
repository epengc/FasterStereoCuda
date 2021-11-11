/* -*-c++-*- SemiGlobalMatching - Copyright (C) 2020.
* Author	: Yingsong Li <ethan.li.whu@gmail.com>
* Describe	: header of DisparityFilter
*/

#ifndef SGM_CUDA_DISP_FILTER_H_
#define SGM_CUDA_DISP_FILTER_H_

#include "sgm_types.h"

class DisparityFilter {
public:
	DisparityFilter();
	~DisparityFilter();

	/**
	 * \brief ��ʼ��
	 * \param width		Ӱ���
	 * \param height	Ӱ���
	 * \return
	 */
	bool Initialize(const sint32& width, const sint32& height);
	
	/** \brief �ͷ��ڴ� */
	void Release();

	/**
	 * \brief �������ݣ��豸�����ݣ�
	 * \param disp_map	�Ӳ�ͼ
	 * \param im_psize	������ͼ��pitch��С
	 * \param dp_psize	���������ͼpitch��С
	 */
	void SetData(uint8* img_bytes, float32* disp_map, const size_t& im_psize, const size_t& dp_psize);

	/**
	 * \brief ���ò���
	 * \param do_median_filter	// ִ����ֵ�˲� 
	 * \param postfilter_type	// �˲���������
	 * \param morphology_type	// ��̬ѧ��������
	 */
	void SetParam(bool do_median_filter, CuSGMOption::PF_Type postfilter_type, CuSGMOption::MP_Type morphology_type);

	/** \brief ִ���˲� */
	void Filter();

	/** \brief ��ȡ������Ӳ�ͼ */
	float32* get_disp_map_out() const;

public:
	// 3x3��ֵ�˲�
	static void Median3X3FilterCuda(float32* d_inout, sint32 width, sint32 height, const size_t& dp_psize);

	// �����˲�������
	static void GaussFilterFloatCuda(float32* d_output, float32* d_input, float32 sigmaD, float32 sigmaR, uint32 width, uint32 height, size_t dp_psize);
	static void BilateralFilterFloatCuda(uint8* img_bytes, float32* d_output, float32* d_input, float32 sigmaD, float32 sigmaR, uint32 width, uint32 height, size_t im_psize, size_t dp_psize);

	// ��̬ѧ��������
	static void ErosionCuda(float32* d_output, float32* d_input, sint32 wndsize, sint32 width, sint32 height, size_t dp_psize);
	static void DilationCuda(float32* d_output, float32* d_input, sint32 wndsize, sint32 width, sint32 height, size_t dp_psize);
	static void ErosionCuda(sint16* d_output, sint16* d_input, sint32 wndsize, sint32 width, sint32 height, size_t dp_psize);
	static void DilationCuda(sint16* d_output, sint16* d_input, sint32 wndsize, sint32 width, sint32 height, size_t dp_psize);

private:
	/** \brief Ӱ��ߴ�*/
	sint32	width_;
	sint32	height_;

	/** \brief ��ͼ������*/
	uint8*	img_bytes_;
	/** \brief �����ͼ��pitch��С*/
	size_t im_psize_;
	/** \brief �Ӳ�ͼ*/
	float32* disp_map_;
	/** \brief ������Ӳ�ͼpitch��С*/
	size_t dp_psize_;
	/** \brief �˲��Ӳ�ͼ*/
	float32* disp_map_filter_;
	/** \brief ����Ӳ�ͼ*/
	float32* disp_map_out_;

	/** \brief ��ֵ�˲�����*/
	bool do_median_filter_;
	/** \brief �����˲�����*/
	CuSGMOption::PF_Type postfilter_type_;
	/** \brief ��̬ѧ������*/
	CuSGMOption::MP_Type morphology_type_;

	/** \brief �Ƿ��ʼ���ɹ� */
	bool is_initialized_;
};

#endif
