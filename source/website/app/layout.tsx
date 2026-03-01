/// CSS Modules
import './globals.css';

/// Vendor Modules
import { Inter } from 'next/font/google';
import { PropsWithChildren } from 'react';

/// Package Modules
import { Provider } from './provider';

/** Font Details. */
const inter = Inter({ subsets: ['latin'] });

/** The core layout component. */
export default function Layout({ children }: PropsWithChildren) {
    return (
        <html lang="en" className={inter.className} suppressHydrationWarning>
            <body className="flex flex-col justify-center items-center min-h-screen w-full">
                <Provider children={children} />
            </body>
        </html>
    );
}
