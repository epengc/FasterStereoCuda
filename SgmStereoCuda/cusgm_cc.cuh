/* -*-c++-*- SemiGlobalMatching - Copyright (C) 2020.
* Author	: Yingsong Li <ethan.li.whu@gmail.com>
* Describe	: header of cusgm_cc
*/

#ifndef SGM_CUDA_COST_COMPUTOR_H_
#define SGM_CUDA_COST_COMPUTOR_H_
#include "sgm_types.h"
#include "cuda_runtime.h"

struct cudaPitchedPtr;

class CostComputor {
public:
	CostComputor();
	~CostComputor();

	/**
	 * \brief ��ʼ��
	 * \param width			Ӱ���
	 * \param height		Ӱ���
	 * \param min_disparity	��С�Ӳ�
	 * \param max_disparity	����Ӳ�
	 * \param cs_mode		Census����ģʽ 0:5x5 1:9x7
	 * \return true: succeed
	 */
	bool Initialize(const sint32& width, const sint32& height, const sint32& min_disparity, const sint32& max_disparity, const sint32& cs_mode = 0);

	/** \brief release memory */
	void Release() const;

	/**
	 * \brief Ϊ���ۼ�����������
	 * \param img_left		����ͼ����
	 * \param img_right		����ͼ����
	 * \param im_psize		������Ӱ�������ֽڿ�
	 */
	void SetData(uint8* img_left, uint8* img_right,const size_t& im_psize);

	/**
	 * \brief Census Transform
	 * \param left			true for computing left view; false for right view 
	 */
	void CensusTransform(const bool& left = true) const;

	/**
	 * \brief ���ۼ���
	 * \param init_disp_mat	��ʼ�Ӳ�ͼ���ӽ������ϲ㴫�ݣ�
	 * \param idp_psize		�������Ӳ�ͼ�ֽڿ�
	 * \param ste_roi		ROI����
	 * \param left2right	true for computing left to right; false for computing right to view,
	 */
	void ComputeCost(sint16* init_disp_mat = nullptr, const size_t& idp_psize = 0, const StereoROI_T* ste_roi = nullptr, const bool& left2right = true) const;

	/** \brief ��ȡ�豸�˳�ʼ����ָ�� */
	cudaPitchedPtr* get_cost_ptr() const;
private:
	/** \brief Ӱ��ߴ� */
	sint32	width_;
	sint32	height_;

	/** \brief Ӱ������ */
	uint8* img_left_;
	uint8* img_right_;
	size_t im_psize_;

	/** \brief ����ͼCensus�任ֵ */
	void* census_left_;
	/** \brief ����ͼCensus�任ֵ */
	void* census_right_;
	/** \brief Census�任ֵ����������ֽڿ�	*/
	size_t cs_psize_;
	/** \brief census transform mode : 0:5x5 1:9x7 */
	sint32 cs_mode_;

	/** \brief ��ʼ���� */
	cudaPitchedPtr* cost_;

	/** \brief min disparity */
	sint32 min_disparity_;
	/** \brief max disparity */
	sint32 max_disparity_;

	/** \brief ��ʼ���ɹ���־ */
	bool is_initialized_;
};

#endif
