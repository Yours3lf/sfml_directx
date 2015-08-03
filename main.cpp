#include <Windows.h>
#include <iostream>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>
#include "DX/d3dx12.h"
#include "SFML/Window.hpp"
#include "mymath/mymath.h"
#include "basic_types.h"

#define WINMSG(X) MessageBox(GetActiveWindow(), (X), "message m8", MB_OK)

int main( int argc, char** args )
{
  //this also creates an opengl context but we dgaf
  //jus gimme teh dam window m8
  sf::Window window( sf::VideoMode( 1280, 720 ), "sfml w/ dx12" );

  window.setVisible( true );

  auto WINCHECK = []( HRESULT hr ) -> void
  {
    if( FAILED( hr ) )
    {
      WINMSG( "WE GOT A PROBLEM, DEBUG M89 :(" );
    }
  };

#ifdef _DEBUG
  //enable dx12 debug stuff
  ID3D12Debug* debug_ctrl = 0;
  D3D12GetDebugInterface( IID_PPV_ARGS( &debug_ctrl ) );

  if( debug_ctrl )
    debug_ctrl->EnableDebugLayer();
#endif

  IDXGIFactory4* fact = 0;
  WINCHECK( CreateDXGIFactory1( IID_PPV_ARGS( &fact ) ) );

  //create device
  ID3D12Device* dank_device = 0;
  WINCHECK( D3D12CreateDevice( 0,
                      //dunny why, but it dont work w/ dx12 feature lvl, surely gotta get sum moar xp 
                      //xDDDddd 
                      //cre8 dx12 device w/ 11 features
                      //REKT m809
                      D3D_FEATURE_LEVEL_11_0,
                      IID_PPV_ARGS( &dank_device ) ) );

  //create cmd queue
  D3D12_COMMAND_QUEUE_DESC cmd_que_m89_desc = {};
  ID3D12CommandQueue* cmd_que_m89 = 0;
  cmd_que_m89_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
  cmd_que_m89_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

  WINCHECK( dank_device->CreateCommandQueue( &cmd_que_m89_desc, IID_PPV_ARGS( &cmd_que_m89 ) ) );

  //create swap chain
  DXGI_SWAP_CHAIN_DESC swapppity_swapp_desc = {};
  swapppity_swapp_desc.BufferCount = 2; //we be double shuffeling m8
  swapppity_swapp_desc.BufferDesc.Width = 1280;
  swapppity_swapp_desc.BufferDesc.Height = 720; //hardcoding is fun :S but gotta go fast
  swapppity_swapp_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //u norm m8?????!?!?
  swapppity_swapp_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //we gon do sum magic, rite?
  swapppity_swapp_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
  swapppity_swapp_desc.OutputWindow = window.getSystemHandle();
  swapppity_swapp_desc.SampleDesc.Count = 1; //no msaa m8, dat ish be old
  swapppity_swapp_desc.Windowed = TRUE; //fullscreen is 3mainstream5me

  Microsoft::WRL::ComPtr<IDXGISwapChain> too_chainz = 0;
  WINCHECK( fact->CreateSwapChain( cmd_que_m89, &swapppity_swapp_desc, &too_chainz ) );

  IDXGISwapChain3* true_chainz = 0;
  Microsoft::WRL::ComPtr<IDXGISwapChain3> bla = 0;
  WINCHECK( too_chainz.As( &bla ) );
  true_chainz = bla.Get();

  unsigned frame_ixDdd = true_chainz->GetCurrentBackBufferIndex();

  //crate descriptor heap for render target views
  D3D12_DESCRIPTOR_HEAP_DESC heapers_gon_heap_desc = {};
  ID3D12DescriptorHeap* heapers_gon_heap = 0;
  heapers_gon_heap_desc.NumDescriptors = 2; //we be double shuffeling m8
  heapers_gon_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; //this is for my homies, the render target views
  heapers_gon_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
  WINCHECK( dank_device->CreateDescriptorHeap( &heapers_gon_heap_desc, IID_PPV_ARGS( &heapers_gon_heap ) ) );

  //sizeof kinda
  unsigned render_target_view_heap_desc_size = dank_device->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );

  //create frame resources (render target view)
  CD3DX12_CPU_DESCRIPTOR_HANDLE gotta_get_dat_memory( heapers_gon_heap->GetCPUDescriptorHandleForHeapStart() );

  ID3D12Resource* render_targets[2] = { 0 };
  for( unsigned c = 0; c < 2; ++c )
  {
    WINCHECK( true_chainz->GetBuffer( c, IID_PPV_ARGS( &render_targets[c] ) ) );
    //create stuff on teh heaper
    dank_device->CreateRenderTargetView( render_targets[c], 0, gotta_get_dat_memory );
    //advance ptr
    gotta_get_dat_memory.Offset( 1, render_target_view_heap_desc_size );
  }

  ID3D12CommandAllocator* teh_cmd_allocator = 0;
  WINCHECK( dank_device->CreateCommandAllocator( D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS( &teh_cmd_allocator ) ) );

  //create thy graphics cmd list
  //woopty woop this is new stuff!!
  ID3D12GraphicsCommandList* dat_graphics_cmd_list;
  WINCHECK( dank_device->CreateCommandList( 0, D3D12_COMMAND_LIST_TYPE_DIRECT, teh_cmd_allocator, 0, IID_PPV_ARGS( &dat_graphics_cmd_list ) ) );

  WINCHECK( dat_graphics_cmd_list->Close() ); //nope, we won't render anything for now NO POLYGONS FOR YAH M989

  //lel this should stop ppl from steppin on ur toes rite?
  ID3D12Fence* hungarian_border_stuff = 0;
  WINCHECK( dank_device->CreateFence( 0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS( &hungarian_border_stuff ) ) );
  u64 fence_val = 1;

  HANDLE fence_evnt = CreateEventEx( 0, 0, 0, EVENT_ALL_ACCESS );
  //maybe handle error here m89??? who cares, just crash...
  if( !fence_evnt )
  {
    int* bla = 0;
    int bal = *bla; //dont do drugs kids
  }

  ID3D12PipelineState* pipe_stuff = 0; //for twenty of course

  //handle input here
  auto event_handler = [&]( const sf::Event & ev )
  {
    switch( ev.type )
    {
      default:
        break;
    }
  };

  auto w8_m8 = [&]() -> void
  {
    //w8 here for prev frame
    u64 fence = fence_val;

    //here comes teh train
    WINCHECK( cmd_que_m89->Signal( hungarian_border_stuff, fence ) );
    ++fence_val;

    //w8 if needed
    if( hungarian_border_stuff->GetCompletedValue() < fence )
    {
      WINCHECK( hungarian_border_stuff->SetEventOnCompletion( fence, fence_evnt ) );
      WaitForSingleObject( fence_evnt, INFINITE ); //to infinity and beyond!
    }

    //advance frame idx
    frame_ixDdd = true_chainz->GetCurrentBackBufferIndex();
  };

  bool run_forest_RUN = 1; //one luv

  //main loop
  while( run_forest_RUN )
  {
    sf::Event ev;
    while( window.pollEvent( ev ) )
    {
      //exit on escape, X button press
      if( ev.type == sf::Event::Closed ||
          ( ev.type == sf::Event::KeyPressed &&
            ev.key.code == sf::Keyboard::Escape ) )
      {
        run_forest_RUN = false;
      }

      //handle all else
      event_handler( ev );
    }

    ///////// cmd list gen
    //render code HAXXX
    WINCHECK( teh_cmd_allocator->Reset() );

    WINCHECK( dat_graphics_cmd_list->Reset( teh_cmd_allocator, pipe_stuff ) );

    //you shall not touch my stuff
    dat_graphics_cmd_list->ResourceBarrier( 1, &CD3DX12_RESOURCE_BARRIER::Transition( render_targets[frame_ixDdd], D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET ) );

    //clear the bg here
    CD3DX12_CPU_DESCRIPTOR_HANDLE render_target_view_handel( heapers_gon_heap->GetCPUDescriptorHandleForHeapStart(), frame_ixDdd, render_target_view_heap_desc_size );

    mm::vec4 skies_ARE_blue( 0.5, 0.5, 0.8, 1 );

    //pass REKT if want only parts
    dat_graphics_cmd_list->ClearRenderTargetView( render_target_view_handel, &skies_ARE_blue.x, 0, 0 );

    //notice reverse order flags
    dat_graphics_cmd_list->ResourceBarrier( 1, &CD3DX12_RESOURCE_BARRIER::Transition( render_targets[frame_ixDdd], D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT ) );

    WINCHECK( dat_graphics_cmd_list->Close() );
    ///////////

    //kick off rendering DO YAH THANG SHAWTY :P
    ID3D12CommandList* cmd_listz[] = { dat_graphics_cmd_list };
    cmd_que_m89->ExecuteCommandLists( _countof( cmd_listz ), cmd_listz );

    //flip them chainz brah!
    WINCHECK( true_chainz->Present( 1, 0 ) );

    //this would present the GL context, so don't do this!
    //window.display();

    w8_m8();
  }

  //kill all stuff
  w8_m8();

  CloseHandle( fence_evnt );

  return 0;
}