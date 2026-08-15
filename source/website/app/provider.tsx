/// Declare Client
'use client';

/// Vendor Modules
import dynamic from 'next/dynamic';
import { PropsWithChildren } from 'react';
import { RootProvider } from 'fumadocs-ui/provider/next';

/** Prepare the search dialog instance. */
const SearchDialog = dynamic(() => import('@/website/components/search').then(({ Search }) => Search), { ssr: true });

/** Core Provider Component. */
export interface Provider extends PropsWithChildren {}
export function Provider({ children }: Provider) {
    return <RootProvider children={children} search={{ SearchDialog }} />;
}
